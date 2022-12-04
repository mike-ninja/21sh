/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trigger_nl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:21:29 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/29 17:15:42 by mrantil          ###   ########.fr       */
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
	ft_run_capability("up");
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
		t->total_row++;
		if (t->start_row + t->total_row >= t->ws_row)
			ft_scroll_down();
		ft_add_nl_last_row(t, t->bytes);
	}
	if (len == t->ws_col + 1)
		if (t->nl_addr[row + 1])
			ft_add_nl_mid_row(t, row + 1, \
				(ssize_t)(&t->nl_addr[row + 1][-1] - t->nl_addr[0]));
	if (t->c_col == t->ws_col)
	{
		t->c_row++;
		t->c_col = 0;
		ft_setcursor(t->c_col, ft_get_linenbr() + 1);
	}
}
