/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trigger_nl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:21:29 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/09 09:40:26 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It scrolls down one line
 */
static void	ft_scroll_down(void)
{
	ft_run_capability("sc");
	ft_run_capability("sf");
	ft_run_capability("rc");
	ft_run_capability("do");
}

/*
 * It adds a newline to the
 * buffer, and if the cursor is at the end of the line, it moves the cursor
 * to the next line
 *
 * @param t the term structure
 */
void	ft_trigger_nl(t_term *t)
{
	ssize_t	len;
	ssize_t	row;

	row = ft_row_lowest_line(t);
	len = ft_len_lowest_line(t, row);
	if (len == t->ws_col)
	{
		if (ft_get_linenbr() == (t->ws_row - 1))
			ft_scroll_down();
		t->total_row++;
		if (t->nl_addr[t->c_row + 1])
		{
			ft_run_capability("cd");
			ft_reset_nl_addr(t);
		}
		else
			ft_add_nl_last_row(t, t->inp, t->bytes);
	}
	if (t->c_col == t->ws_col)
	{
		t->c_row++;
		t->c_col = 0;
		ft_setcursor(t->c_col, ft_get_linenbr() + 1);
	}
}
