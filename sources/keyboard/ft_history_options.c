/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_options.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:45:11 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/23 19:51:28 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void history_option_display(char *str)
{
    while (*str)
    {
        if (*str != '\n')
            ft_putchar(*str);
        else
            ft_putstr("\\n");
        str++;
    }
}

void	history_options(t_term *t, t_search_history *config)
{
	int	index;
	int	row_cpy;
	int	to_show_cpy;
	int	display_row_cpy;
	int	history_index_cpy;

	ft_run_capability("vi");
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
			// ft_printf("%2s%-5d%2s%s", "", history_index_cpy, "", t->history_arr[history_index_cpy]);
			ft_printf("%2s%-5d%2s", "", history_index_cpy, "");
            history_option_display(t->history_arr[history_index_cpy]);
			display_row_cpy--;
			row_cpy--;
			config->ptr[index++] = history_index_cpy;
			to_show_cpy--;
		}
		history_index_cpy--;
	}
	config->index = (config->history_rows - row_cpy) - 1;
	while (row_cpy-- > 0)
	{
		ft_setcursor(0, display_row_cpy--);
		ft_run_capability("ce");
	}
	ft_run_capability("ve");
}
