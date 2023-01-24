/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_history.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:36:20 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/24 11:32:00 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	init_index_ptr(t_search_history *config)
{
	int	i;

	i = -1;
	config->ptr = (int *)ft_memalloc(sizeof(int) * (config->history_rows));
	while (++i < config->history_rows)
		config->ptr[i] = -1;
}

static void	init_search_history_config(t_term *t, t_search_history *config)
{
	config->match = 0;
	config->history_rows = 10;
	init_index_ptr(config);
	config->max_to_show = 50;
	if (t->history_size < (size_t)config->max_to_show)
		config->max_to_show = t->history_size - 1;
	config->to_show = config->max_to_show - 1;
	config->history_index = t->history_size - 1;
	config->start_cur_row = t->term_val[1] + t->total_row;
	config->match = count_matches(t, config);
	config->row = config->start_cur_row + (config->history_rows - 1);
	config->match_term_row = config->row + 1;
	config->input_term_row = config->row + 2;
}

static void	ft_display_input(t_term *t, t_search_history *config)
{
	ft_setcursor(0, config->input_term_row);
	print_selector("BLUE");
	ft_run_capability("nd");
	config->input_cur_col = 2;
	config->input_cur_col += write(1, t->nl_addr[t->total_row], \
	ft_strlen(t->nl_addr[t->total_row]));
}

static void	ft_display_to_show(t_search_history *config)
{
	ft_setcursor(0, config->match_term_row);
	ft_run_capability("ce");
	ft_printf("{CYAN}%2s%d/%d %cS{RESET}", "", config->match, \
	config->max_to_show, '+');
}

void	init_interface(t_term *t, t_search_history *config)
{
	int	diff;

	ft_run_capability("cb");
	ft_run_capability("cd");
	diff = config->input_term_row - t->ws_row;
	if (diff >= 0)
	{
		ft_run_capability("sc");
		config->start_cur_row -= diff + 1;
		t->term_val[1] -= diff + 1;
		while (diff-- >= 0)
		{
			ft_setcursor(0, t->ws_row);
			ft_run_capability("sf");
		}
		config->row = t->ws_row - 3;
		config->match_term_row = config->row + 1;
		config->input_term_row = config->row + 2;
		ft_run_capability("rc");
	}
}

static void	edit_input(int *i_cpy, int *r_cpy, t_term *t, t_search_history *config)
{
	bool bs;

	bs = false;
	if (config->inp == BACKSPACE && &t->inp[t->index] > t->nl_addr[t->total_row])
		bs = true;
	if (!ft_isprint(config->inp) && !bs)
		return ;
	if (ft_isprint(config->inp) && config->input_cur_col == (t->ws_col - 1))
		return ;
	config->row = config->start_cur_row + (config->history_rows - 1);
	*r_cpy = config->row;
	ft_setcursor(1, config->row);
	ft_run_capability("cb");
	if (bs)
	{
		ft_deletion_shift(t, --t->index);
		--config->input_cur_col;
	}
	else
	{
		t->inp[t->index++] = config->inp;
		++t->bytes;
		++config->input_cur_col;
	}
	config->history_index = t->history_size - 1;
	config->match = count_matches(t, config);
	config->to_show = config->match - 1;
	history_options(t, config);
	*i_cpy = config->index;
	ft_display_to_show(config);
	ft_display_input(t, config);
	if (config->to_show)
	{
		ft_setcursor(0, config->row);
		print_selector("RED");
	}
	ft_setcursor(config->input_cur_col, config->input_term_row);
	if (bs)
		ft_run_capability("ce");
}

void	ft_search_history(t_term *t)
{
	int					row_cpy;
	int					index_cpy;
	t_search_history	config;

	// Need to setup signals for sigwinch, sigint
	ft_run_capability("vi");
	init_search_history_config(t, &config);
	init_interface(t, &config);
	history_options(t, &config);
	ft_display_to_show(&config);
	ft_display_input(t, &config);
	ft_setcursor(0, config.row);
	print_selector("RED");
	row_cpy = config.row;
	index_cpy = config.index;
	ft_setcursor(config.input_cur_col, config.input_term_row);
	ft_run_capability("ve");
	while (true)
	{
		config.inp = ft_get_input();
		if (config.inp == 91)
		{
			ft_run_capability("vi");
			config.inp = ft_get_input();
			if (config.inp == 65 && config.to_show)
				ft_selector_up(&index_cpy, &row_cpy, t, &config);
			else if (config.inp == 66 && config.to_show < config.max_to_show)
				ft_selector_do(&index_cpy, &row_cpy, t, &config);
			ft_run_capability("ve");
		}
		else if (config.inp == '\n')
		{
			ft_select_history(t, &config, index_cpy);
			break ;
		}
		else if (ft_isprint(config.inp) || config.inp == BACKSPACE)
			edit_input(&index_cpy, &row_cpy, t, &config);
		else if (config.inp == 18)
		{
			if (!t->total_row)
				t->c_col = t->prompt_len;
			else
				t->c_col = t->m_prompt_len;
			t->c_col += ft_strlen(t->nl_addr[t->total_row]);
			ft_setcursor(0, config.start_cur_row);
			ft_run_capability("cd");
			ft_print_input(t, t->c_row, 0);
			ft_memdel((void **)&config.ptr);
			break ;
		}
	}
}

