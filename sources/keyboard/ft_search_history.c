/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_history.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:36:20 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/23 10:57:01 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void print_prompt(char *color)
{	
	if (!ft_strcmp("RED", color))
		ft_printf("{RED}>{RESET}");
	if (!ft_strcmp("BLUE", color))
		ft_printf("{BLUE}>{RESET}");
}

static int	count_matches(t_term *t, int max_to_show)
{
	int	i;
	int	count;
	int	to_show;

	count = 0;
	to_show = 0;
	i = t->history_size ;
	while (to_show < max_to_show)
	{
		if (ft_strstr(t->history_arr[--i], t->nl_addr[t->total_row]))
			count++;
		to_show++;
	}
	return (count);
}

void	init_index_ptr(t_search_history *config)
{
	int i;
	
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
	config->max_to_show = 30;
	config->to_show = config->max_to_show - 1;
	config->history_index = t->history_size - 1;
	config->start_cur_row = t->term_val[1] + t->total_row;
	config->match = count_matches(t, config->max_to_show);
	config->row = config->start_cur_row + (config->history_rows - 1);
}

static void	ft_display_input(t_term *t, t_search_history *config)
{
	ft_setcursor(0, config->row + 2);
	print_prompt("BLUE");
	ft_run_capability("nd");
	ft_putstr(t->nl_addr[t->total_row]);
}

static void ft_display_to_show(t_search_history *config)
{
 	ft_setcursor(0, config->row + 1);
	ft_printf("{CYAN}%2s%d/%d %cS{RESET}", "", config->match, config->max_to_show, '+');
}

void	init_interface(t_term *t, t_search_history *config)
{
	int	diff;

	ft_run_capability("cb");
	ft_run_capability("cd");
	diff = (config->row + 2) -  t->ws_row;
	if (diff >= 0)
	{
		ft_run_capability("sc");
		config->start_cur_row -= diff + 1;
		while (diff-- >= 0)
		{
			ft_setcursor(0, t->ws_row);
			ft_run_capability("sf");
		}
		config->row = t->ws_row - 3;
		ft_run_capability("rc");
	}
	ft_display_input(t, config);
	ft_display_to_show(config);
}

void	history_options(t_term *t, t_search_history *config)
{
	int	index;
	int	row_cpy;
	int	to_show_cpy;
	int	display_row_cpy;
	int	history_index_cpy;

	index = 0;
	display_row_cpy =  config->row;
	row_cpy = config->history_rows;
	history_index_cpy = config->history_index;
	to_show_cpy = config->to_show + config->history_rows;
	while (row_cpy && history_index_cpy && t->history_arr[history_index_cpy] && to_show_cpy && index < config->match)
	{
		if (ft_strstr(t->history_arr[history_index_cpy], t->nl_addr[t->total_row])) // This logic needs to be improved
		{
			ft_setcursor(0, display_row_cpy);
			ft_run_capability("ce");
			ft_printf("%2s%d%5s%s", "", history_index_cpy, "", t->history_arr[history_index_cpy]);
			ft_run_capability("up");
			display_row_cpy--;
			row_cpy--;
			config->ptr[index++] = history_index_cpy;
			to_show_cpy--;
		}
		history_index_cpy--;
	}
	config->index = (config->history_rows - row_cpy) - 1;
}

static void	ft_selector_do(int *index_cpy, int *row_cpy, t_term *t, t_search_history *config)
{
	if ((*index_cpy) < config->index)
	{ 
		++(*row_cpy);
		++(*index_cpy);
		++config->to_show;
		ft_run_capability("cb");
	}
	else if ((size_t)config->history_index < (t->history_size - 1))
	{
		++config->to_show;
		++config->history_index;
		history_options(t, config);
	}
	ft_setcursor(0, *row_cpy);
	print_prompt("RED");
}

static void	ft_selector_up(int *index_cpy, int *row_cpy, t_term *t, t_search_history *config)
{
	if (*index_cpy)
	{
		--(*row_cpy);
		--(*index_cpy);
		--config->to_show;
		ft_run_capability("cb");
	}
	else if (config->index == (config->history_rows - 1) && config->ptr[config->index - (*index_cpy)] > 1)
	{
		--config->to_show;
		--config->history_index;
		history_options(t, config);
	}
	ft_setcursor(0, *row_cpy);
	print_prompt("RED");
}

static void	ft_select_history(t_term *t, t_search_history *config, int index_cpy)
{
	t->c_col = ft_strlen(t->history_arr[config->ptr[config->index - index_cpy]]);
	t->bytes -= ft_strlen(t->nl_addr[t->total_row]);
	ft_memcpy(t->nl_addr[t->total_row], t->history_arr[config->ptr[config->index - index_cpy]], t->c_col);
	t->term_val[1] = config->start_cur_row;
	t->bytes += t->c_col;
	t->index = t->bytes;
	ft_setcursor(0, config->start_cur_row);
	ft_run_capability("cd");
	if (!t->total_row)
	{
		ft_printf("{GREEN}%s{RESET}", PROMPT);
		t->c_col += t->prompt_len;
	}
	else
	{
		ft_printf("{GREEN}%s{RESET}", MINI_PROMPT);
		t->c_col += t->m_prompt_len;
	}
	ft_putstr(t->nl_addr[t->total_row]);
	ft_memdel((void **)&config->ptr);	
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
	ft_setcursor(0, config.row);
	history_options(t, &config);
	ft_setcursor(0, config.row);
	print_prompt("RED");
	row_cpy = config.row;
	index_cpy = config.index;
	if (config.index == -1) // When there is no matches found?
		return ;
	while (true) // while loop for the selector
	{
		config.inp = ft_get_input();
		if (config.inp == 'q')
			break;
		if (config.inp == 91)
		{
			config.inp = ft_get_input();
			if (config.inp == 65 && config.to_show) // up
				ft_selector_up(&index_cpy, &row_cpy, t, &config);
			if (config.inp == 66 && config.to_show < config.max_to_show) // do
				ft_selector_do(&index_cpy, &row_cpy, t, &config);
		}
		if (config.inp == '\n')
		{
			ft_select_history(t, &config, index_cpy);
			break;
		}
	}
	ft_run_capability("ve");
}
