/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_history.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:36:20 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/21 15:00:50 by mbarutel         ###   ########.fr       */
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
	// if (config->ptr)
	// 	ft_memdel((void **)&config->ptr);
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
	config->start_cur_row = t->term_val[1] + t->c_row;
	config->match = count_matches(t, config->max_to_show);
	config->row = config->start_cur_row + (config->history_rows - 1);
}



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
}

void	history_options(t_term *t, t_search_history *config) // This should return the amount of lines printed
{
	int	index;
	int	row_cpy;
	int	to_show_cpy;
	int	display_row_cpy;
	int	history_index_cpy;

	index = 0;
	row_cpy = config->history_rows;
	history_index_cpy = config->history_index;
	to_show_cpy = config->to_show + config->history_rows;
	display_row_cpy =  config->start_cur_row + (config->history_rows - 1);
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

void	ft_search_history(t_term *t)
{
	int					row_cpy;
	int					index_cpy;
	t_search_history	config;
	
	
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
			{
				if (index_cpy)
				{
					--row_cpy;
					--index_cpy;
					--config.to_show;
					ft_run_capability("cb");
				}
				else if (config.index == (config.history_rows - 1) && config.ptr[config.index - index_cpy] > 1)
				{
					--config.to_show;
					--config.history_index;
					history_options(t, &config);
				}
				ft_setcursor(0, row_cpy);
				print_prompt("RED");
					
			}
			if (config.inp == 66 && config.to_show < config.max_to_show) // do
			{
				if (index_cpy < config.index)
				{
					++row_cpy;
					++index_cpy;
					++config.to_show;
					ft_run_capability("cb");
				}
				else if ((size_t)config.history_index < (t->history_size - 1))
				{
					++config.to_show;
					++config.history_index;
					history_options(t, &config);
				}
				ft_setcursor(0, row_cpy);
				print_prompt("RED");
			}
		}
		if (config.inp == '\n')
		{
			ft_run_capability("cl");
			ft_printf("|%s|", t->history_arr[config.ptr[config.index - index_cpy]]);
			ft_memdel((void **)&config.ptr);
			break;
		}
	}
	ft_run_capability("ve");
}
