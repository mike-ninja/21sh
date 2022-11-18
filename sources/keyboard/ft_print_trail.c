/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_trail.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:40:06 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/18 16:12:01 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	ft_print_prompt(ssize_t row)
{
	if (!row)
		ft_putstr(PROMPT);
	else
		ft_putstr(M_PROMPT);
}

static void	ft_print_line_trail(t_term *t)
{
	ssize_t	row;
	ssize_t dis_row;

	row = t->c_row;
	dis_row = ft_get_linenbr();
	while (row <= t->total_row)
	{
		ft_run_capability("ce");
		if (row == t->c_row)
		{
			if (t->nl_addr[row + 1])
				write(1, &t->inp[t->index], (size_t)(t->nl_addr[row + 1] - &t->inp[t->index]));
			else
				write(1, &t->inp[t->index], (size_t)((&t->inp[t->bytes] - &t->inp[t->index]) + 1));	
		}
		else
		{
			if (ft_is_prompt_line(t, row))
				ft_print_prompt(row);
			if (t->nl_addr[row + 1])
				write(1, t->nl_addr[row], (size_t)(t->nl_addr[row + 1] - t->nl_addr[row]));
			else
				write(1, t->nl_addr[row], (size_t)((&t->inp[t->bytes] - t->nl_addr[row]) + 1));
		}
		ft_setcursor(0, ++dis_row);
		row++;
	}
}

void	ft_print_trail(t_term *t)
{
	// ssize_t row;

	ft_run_capability("vi");
	ft_run_capability("sc");
	// ft_run_capability("sf");
	// row = ft_get_linenbr();
	ft_run_capability("vi");
	ft_print_line_trail(t);
	ft_run_capability("rc");
	ft_run_capability("ve");
	// ft_setcursor(t->c_col, row);
	// ft_run_capability("ve");
}
