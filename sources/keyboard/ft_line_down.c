/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_down.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:25:34 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/29 16:47:26 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * If the cursor is not at the end of the line, move it to the end of the line
 *
 * @param t the term structure
 * @param len the length of the current line
 * @param prompt_len The length of the prompt.
 */
static void	ft_move_down_end_line(t_term *t, ssize_t len, ssize_t prompt_len)
{
	t->c_col = len + prompt_len;
	if (t->c_row < (t->total_row - 1))
	{
		t->c_col--;
		t->index = &t->nl_addr[t->c_row + 2][-1]
			- t->nl_addr[0];
	}
	else
		t->index = (&t->inp[t->bytes] - t->nl_addr[0]);
}

/*
 * It moves the cursor down one line
 *
 * @param t the term structure
 * @param prompt_len the length of the prompt
 */
static void	ft_move_down(t_term *t, ssize_t prompt_len)
{
	if (t->c_col < prompt_len)
	{
		t->c_col = prompt_len;
		t->index = t->nl_addr[t->c_row + 1] - t->nl_addr[0];
	}
	t->index = &t->nl_addr[t->c_row + 1][t->c_col - prompt_len] \
		- t->nl_addr[0];
}

/*
 * It moves the cursor down one line
 *
 * @param t the term structure
 */
void	ft_line_down(t_term *t)
{
	ssize_t	len;
	ssize_t	prompt_len;

	prompt_len = ft_mv_prompt_len(t, 1);
	if (t->c_row < (t->total_row - 1))
		len = (t->nl_addr[t->c_row + 2] - t->nl_addr[t->c_row + 1]);
	else
		len = &t->inp[t->bytes] - t->nl_addr[t->c_row + 1];
	if (t->c_col < (len + prompt_len))
		ft_move_down(t, prompt_len);
	else
		ft_move_down_end_line(t, len, prompt_len);
	t->c_row++;
	ft_setcursor(t->c_col, (ft_get_linenbr() + 1));
}
