/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_history.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:36:20 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/19 21:48:03 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	history_options(t_term *t, int row, int display_row, size_t history_index)
{
	// ssize_t history;

	// history = t->history_size - 1;
	while (row && history_index && t->history_arr[history_index])
	{
		if (ft_strstr(t->history_arr[history_index], t->inp))
		{
			ft_setcursor(0, display_row);
			ft_run_capability("ce");
			ft_printf("%2s%d%5s%s", "", history_index, "", t->history_arr[history_index]);
			ft_run_capability("up");
			display_row--;
			row--;
		}
		history_index--;
	}
}

// static size_t	start_row(t_term *t, int num)
// {
// 	size_t	row_req;
// 	size_t	row;

// 	row_req = 10; // This can be assigned via env variable;
// 	row_req += num;
// 	if (t->history_size > row_req)
// 		row = (t->history_size - row_req);
// 	else
// 		row = 0;
// 	return (row);
// }

static void print_prompt(void)
{	
	ft_printf("{RED}>{RESET}");
}

void	ft_search_history(t_term *t)
{
	ssize_t	cur_row;
	int	row_req;
	int	history_row_cur;
	char	inp;
	ssize_t	index;
	ssize_t row;

	row_req = 10;
	cur_row = t->term_val[1] + t->c_row;
	// ft_run_capability("cb");
	// ft_run_capability("ce");
	history_row_cur = t->history_size - 1;
	// ft_run_capability("cb");
	ft_run_capability("cd");
	ft_setcursor(0, cur_row + (row_req - 1));
	history_options(t, 10, cur_row + (row_req - 1), history_row_cur); // print the options
	ft_setcursor(0, cur_row + (row_req - 1));
	// row = row_req;
	row = cur_row + (row_req - 1);
	ft_run_capability("vi");
	print_prompt();
	index = row_req - 1;
	while (true) // while loop for the selector
	{
		inp = ft_get_input();
		if (inp == 'q')
			break;
		if (inp == 91)
		{
			inp = ft_get_input();
			if (inp == 65) // up
			{
				if (row > cur_row)
				{
					ft_run_capability("cb");
					--row;
					--index;
				}
				else
				{
					history_options(t, 10, cur_row + (row_req - 1), --history_row_cur);
				}
				ft_setcursor(0, row);
				print_prompt();
					
			}
			if (inp == 66) // do
			{
				if (row < (cur_row + (row_req - 1)))
				{
					ft_run_capability("cb");
					++row;
					++index;
				}
				else if ((size_t)history_row_cur < t->history_size)
				{
					history_options(t, 10, cur_row + (row_req - 1), ++history_row_cur);	
				}
				ft_setcursor(0, row);
				print_prompt();
			}
		}
		if (inp == '\n')
			break;
		// ft_printf("%d\n", inp); // up 91:65 do 91:66
	}
	ft_run_capability("ve");
}
