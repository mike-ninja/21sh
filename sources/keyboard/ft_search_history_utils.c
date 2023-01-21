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

void	init_index_ptr(t_search_history *config)
{
	int i;
	
	i = -1;
	if (config->ptr)
		ft_memdel((void **)&config->ptr);
	config->ptr = (int *)ft_memalloc(sizeof(int) * (config->history_rows));
	while (++i < config->history_rows)
		config->ptr[i] = -1;
}

// int	init_interface(t_term *t, int history_rows, ssize_t start_cur_row, int *match, int max_to_show)
void	init_interface(t_term *t, t_search_history *config)
{
	ft_run_capability("cb");
	ft_run_capability("cd");
	ft_setcursor(0, config->row + 2);
	print_prompt("BLUE");
	ft_run_capability("nd");
	ft_putstr(t->nl_addr[t->total_row]);
	ft_setcursor(0, config->row + 1);
	ft_printf("");
	ft_printf("{CYAN}%2s%d/%d %cS{RESET}", "", config->match, config->max_to_show, '+');
	// ft_setcursor(0, start_cur_row + (history_rows - 1));
	// history_options(t, history_rows, start_cur_row + (history_rows - 1), history_index);
	// ft_setcursor(0, start_cur_row + (history_rows - 1));
	// print_prompt("RED");
	
	// setup the 2 other lines
}


// history_options(t, history_rows, start_cur_row + (history_rows - 1), history_index, ptr, to_show, match);

void	history_options(t_term *t, t_search_history *config) // This should return the amount of lines printed
{
	int	index;
	int	row_cpy;
	int	to_show_cpy;
	int	display_row_cpy;
	int	history_index_cpy;

	index = -1;
	row_cpy = config->history_rows;
	to_show_cpy = config->to_show + config->row;
	display_row_cpy =  config->start_cur_row + (config->history_rows - 1);
	history_index_cpy = config->history_index;
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
			config->ptr[++index] = history_index_cpy;
			to_show_cpy--;
		}
		history_index_cpy--;
	}
	config->index = (config->history_rows - row_cpy) - 1;
}