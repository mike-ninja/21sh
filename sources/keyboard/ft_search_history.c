/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_history.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:36:20 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/20 14:56:36 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static size_t	history_options(t_term *t, int row, int display_row, size_t history_index, int *ptr) // This should return the amount of lines printed
{
	int row_cpy;
	int	i;

	i = -1;
	row_cpy = row;
	while (row && history_index && t->history_arr[history_index])
	{
		if (ft_strstr(t->history_arr[history_index], t->nl_addr[t->c_row])) // This logic needs to be improved
		{
			ft_setcursor(0, display_row);
			ft_run_capability("ce");
			ft_printf("%2s%d%5s%s", "", history_index, "", t->history_arr[history_index]);
			ft_run_capability("up");
			display_row--;
			row--;
			ptr[++i] = history_index;
		}
		history_index--;
	}
	return ((row_cpy - row) - 1);
}

static void print_prompt(char *color)
{	
	if (!ft_strcmp("RED", color))
		ft_printf("{RED}>{RESET}");
	if (!ft_strcmp("BLUE", color))
		ft_printf("{BLUE}>{RESET}");
}

static int	init_interface(t_term *t, int history_rows, ssize_t start_cur_row)
{
	ft_run_capability("cb");
	ft_run_capability("cd");
	ft_setcursor(0, start_cur_row + (history_rows - 1) + 2);
	print_prompt("BLUE");
	ft_run_capability("nd");
	ft_putstr(t->nl_addr[t->c_row]);
	// ft_setcursor(0, start_cur_row + (history_rows - 1));
	// history_options(t, history_rows, start_cur_row + (history_rows - 1), history_index);
	// ft_setcursor(0, start_cur_row + (history_rows - 1));
	// print_prompt("RED");
	
	// setup the 2 other lines
	return (start_cur_row + (history_rows - 1));
}

void	ft_search_history(t_term *t)
{
	int			history_index;
	int			history_rows;
	ssize_t		start_cur_row;
	ssize_t		index_limit;
	ssize_t		index;
	ssize_t		row;
	char		inp;
	int			*ptr;	
	

	ptr = NULL;
	ft_run_capability("vi");
	history_rows = 10;
	history_index = t->history_size - 1;
	start_cur_row = t->term_val[1] + t->c_row;
	row = init_interface(t, history_rows, start_cur_row);

	/* Trial here */
	ft_setcursor(0, start_cur_row + (history_rows - 1));
	/* Init int ptr */
	ptr = (int *)ft_memalloc(sizeof(int) * (history_rows));
	
	int i;

	i = -1;
	while (++i < history_rows)
		ptr[i] = 0;
	/* Init int ptr */
	index_limit = history_options(t, history_rows, start_cur_row + (history_rows - 1), history_index, ptr);
	ft_setcursor(0, start_cur_row + (history_rows - 1));
	print_prompt("RED");
	/* Trial here */
	index = index_limit;
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
				if (index)
				{
					ft_run_capability("cb");
					--row;
					--index;
				}
				else if ((size_t)history_index - history_rows && index_limit == (history_rows - 1))
				{
					--history_index;
					ft_memdel((void **)&ptr);
					ptr = (int *)ft_memalloc(sizeof(int) * (history_rows));

					i = -1;
					while (++i < history_rows)
						ptr[i] = 0;
					index_limit = history_options(t, 10, start_cur_row + (history_rows - 1), history_index, ptr);
				}
				ft_setcursor(0, row);
				print_prompt("RED");
					
			}
			if (inp == 66) // do
			{
				if (index < index_limit)
				{
					ft_run_capability("cb");
					++row;
					++index;
				}
				else if ((size_t)history_index < (t->history_size - 1))
				{
					++history_index;
					ft_memdel((void **)&ptr);
					ptr = (int *)ft_memalloc(sizeof(int) * (history_rows));

					i = -1;
					while (++i < history_rows)
						ptr[i] = 0;
					index_limit = history_options(t, 10, start_cur_row + (history_rows - 1), history_index, ptr);	
				}
				ft_setcursor(0, row);
				print_prompt("RED");
			}
		}
		if (inp == '\n')
		{
			ft_run_capability("cl");
			ft_printf("|%s|", t->history_arr[ptr[index_limit - index]]);
			ft_memdel((void **)&ptr);
			break;
		}
	}
	ft_run_capability("ve");
}
