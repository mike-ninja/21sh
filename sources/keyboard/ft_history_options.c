/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_options.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:45:11 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/24 12:25:59 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void history_option_display(t_term *t, char *str)
{
	int	col;

	col = 10;
    while (*str)
    {
        if (*str != '\n')
            ft_putchar(*str);
        else
		{
            ft_putstr("\\n");
			col++;
		}
        str++;
		col++;
		if (col == t->ws_col - 3)
		{
			ft_putstr("..");
			break ;
		}
	}
}

bool	ft_is_match(char *haystack, char *needle)
{
	int	x;
	int	len;

	x = 0;
	len = ft_strlen(needle);
	while (*haystack && needle[x])
	{
		if (*haystack == needle[x])
			++x;
		haystack++;
	}
	if (x == len)
		return (1);
	else
		return (0);
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
		// if (ft_strstr(t->history_arr[history_index_cpy], t->nl_addr[t->total_row])) // This logic needs to be improved
		if (ft_is_match(t->history_arr[history_index_cpy], t->nl_addr[t->total_row])) // This logic needs to be improved
		{
			ft_setcursor(0, display_row_cpy);
			ft_run_capability("ce");
			ft_printf("%2s%-5d%2s", "", history_index_cpy, "");
            history_option_display(t, t->history_arr[history_index_cpy]);
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
