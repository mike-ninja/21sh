/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_esc_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:31:54 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/29 16:40:29 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It moves the cursor to the beginning of the line
 *
 * @param t the term structure
 */
static void	ft_cursor_beginning(t_term *t)
{
	if (!t->c_row)
	{
		t->c_col = t->prompt_len;
		t->index = 0;
	}
	else
	{
		if (ft_is_prompt_line(t, t->c_row))
			t->c_col = t->m_prompt_len;
		else
			t->c_col = 0;
		t->index = t->nl_addr[t->c_row] - t->nl_addr[0];
	}
	ft_setcursor(t->c_col, ft_get_linenbr());
}

/*
 * It moves the cursor to the end of the line
 *
 * @param t the term structure
 */
static void	ft_cursor_end(t_term *t)
{
	ssize_t	len;

	t->c_col = 0;
	len = t->index;
	if (!t->c_row || ft_is_prompt_line(t, t->c_row))
	{
		if (!t->c_row)
			t->c_col = t->prompt_len;
		else
			t->c_col = t->m_prompt_len;
	}
	if (t->nl_addr[t->c_row + 1])
		t->index = (t->nl_addr[t->c_row + 1] - t->nl_addr[0]) - 1;
	else
		t->index = t->bytes;
	len = t->index - len;
	t->c_col += &t->inp[t->index] - t->nl_addr[t->c_row];
	ft_setcursor(t->c_col, ft_get_linenbr());
}

/*
 * It moves the cursor to the beginning or end of the line
 *
 * @param t the term structure
 */
static void	shift_arrow(t_term *t)
{
	if (t->ch == ARROW_RGHT && t->bytes)
		ft_cursor_beginning(t);
	if (t->ch == ARROW_LFT)
		ft_cursor_end(t);
}

/*
 * It parses the escape sequence and calls the appropriate function
 *
 * @param t the term structure
 */
void	ft_esc_parse(t_term *t)
{
	t->ch = ft_get_input();
	if (t->ch == '[')
	{
		t->ch = ft_get_input();
		if (t->ch >= ARROW_UP && t->ch <= ARROW_RGHT)
			ft_arrow_input(t);
		if (t->ch == LINE_MV)
			ft_alt_mv(t);
		if (t->ch == CURS_BIGIN && t->bytes)
			ft_cursor_beginning(t);
		if (t->ch == CURS_END)
			ft_cursor_end(t);
		if (t->ch == KEY_SHIFT)
		{
			t->ch = ft_get_input();
			shift_arrow(t);
		}
	}
	if (t->ch == ALT_LFT || t->ch == ALT_RGHT)
		ft_alt_mv(t);
	t->ch = 0;
}
