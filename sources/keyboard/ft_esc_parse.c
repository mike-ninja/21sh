/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_esc_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:31:54 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/21 11:25:38 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

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

static void	shift_arrow(t_term *t)
{
	if (t->ch == 'D' && t->bytes)
		ft_cursor_beginning(t);
	if (t->ch == 'C')
		ft_cursor_end(t);
}

void	ft_esc_parse(t_term *t)
{
	t->ch = ft_get_input();
	if (t->ch == '[')
	{
		t->ch = ft_get_input();
		if (t->ch >= 'A' && t->ch <= 'D')
			ft_arrow_input(t);
		if (t->ch == 49)
			ft_opt_mv(t);//why two of these? line 92
		if (t->ch == 'H' && t->bytes)
			ft_cursor_beginning(t);
		if (t->ch == 'F')
			ft_cursor_end(t);
		if (t->ch == '2')
		{
			t->ch = ft_get_input();
			shift_arrow(t);
		}
	}
	if (t->ch == 98 || t->ch == 102)
		ft_opt_mv(t);
	t->ch = 0;
}
