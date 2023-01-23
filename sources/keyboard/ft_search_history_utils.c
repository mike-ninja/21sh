/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_seash_history_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 11:46:54 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/21 12:18:5 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	print_selector(char *color)
{	
	if (!ft_strcmp("RED", color))
		ft_printf("{RED}>{RESET}");
	if (!ft_strcmp("BLUE", color))
		ft_printf("{BLUE}>{RESET}");
}

int	count_matches(t_term *t, t_search_history *config)
{
	int	i;
	int	count;
	int	to_show;

	count = 0;
	to_show = 0;
	i = config->history_index;
	if (*t->nl_addr[t->total_row] == '\0')
		return (config->max_to_show);
	while (i && to_show < config->max_to_show)
	{
		if (ft_strstr(t->history_arr[i], t->nl_addr[t->total_row]))
		{
			count++;
			to_show++;
		}
		i--;
	}
	return (count);
}

static void	get_next_index(t_term *t, t_search_history *config)
{
	if ((size_t)config->history_index < (t->history_size - 1))
	{
		config->history_index++;
		if (*t->nl_addr[t->total_row])
		{
			while ((size_t)config->history_index < (t->history_size - 1) \
			&& !ft_strstr(t->history_arr[config->history_index], \
			t->nl_addr[t->total_row]))
				config->history_index++;
		}
	}	
}

void	ft_selector_do(int *i_cpy, int *r_cpy, t_term *t, \
t_search_history *config)
{
	ft_setcursor(0, *r_cpy);
	if ((*i_cpy) < config->index)
	{
		++(*r_cpy);
		++(*i_cpy);
		++config->to_show;
		ft_run_capability("cb");
	}
	else if ((size_t)config->history_index < (t->history_size - 1))
	{
		++config->to_show;
		config->history_index = config->ptr[0];
		get_next_index(t, config);
		history_options(t, config);
	}
	ft_setcursor(0, *r_cpy);
	print_selector("RED");
	ft_setcursor(config->input_cur_col, config->input_term_row);
}

void	ft_selector_up(int *i_cpy, int *r_cpy, t_term *t, \
t_search_history *config)
{
	ft_setcursor(0, *r_cpy);
	if (*i_cpy > 0)
	{
		--(*r_cpy);
		--(*i_cpy);
		--config->to_show;
		ft_run_capability("cb");
	}
	else if (config->index == (config->history_rows - 1) \
	&& config->ptr[config->index - (*i_cpy)] > 1)
	{
		--config->to_show;
		config->history_index = config->ptr[1];
		history_options(t, config);
	}
	ft_setcursor(0, *r_cpy);
	print_selector("RED");
	ft_setcursor(config->input_cur_col, config->input_term_row);
}

void	ft_select_history(t_term *t, t_search_history *config, int index_cpy)
{
	if (config->index >= 0 && index_cpy >= 0)
	{
		t->c_col = ft_strlen(t->history_arr \
		[config->ptr[config->index - index_cpy]]);
		t->bytes -= ft_strlen(t->nl_addr[t->total_row]);
		ft_memcpy(t->nl_addr[t->total_row], t->history_arr \
		[config->ptr[config->index - index_cpy]], t->c_col);
		t->bytes += t->c_col;
		t->index = t->bytes;
	}
	ft_setcursor(0, config->start_cur_row);
	ft_run_capability("cd");
	ft_history_reset_nl(t);
	ft_quote_flag_reset(t);
	ft_print_input(t, t->c_row, 0);
	t->c_row = t->total_row;
	ft_memdel((void **)&config->ptr);
}
