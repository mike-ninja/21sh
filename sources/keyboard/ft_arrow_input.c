/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrow_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:27:59 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/21 11:15:00 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	ft_right(t_term *t)
{
	ssize_t	row;

	if (&t->inp[t->index] == &t->nl_addr[t->c_row + 1][-1]
		&& ft_is_prompt_line(t, t->c_row + 1))
		return ;
	row = (ssize_t)ft_get_linenbr();
	if (&t->inp[t->index] == &t->nl_addr[t->c_row + 1][-1])
	{
		t->c_col = -1;
		t->c_row++;
		row++;
	}
	t->index++;
	ft_setcursor(++t->c_col, row);
}

static void	ft_left(t_term *t)
{
	ssize_t	row;

	if (&t->inp[t->index] == t->nl_addr[t->c_row]
		&& ft_is_prompt_line(t, t->c_row))
		return ;
	row = (ssize_t)ft_get_linenbr();
	if (&t->inp[t->index] == t->nl_addr[t->c_row])
	{
		t->c_col = 0;
		if (t->c_row == 1)
			t->c_col = t->prompt_len;
		else if (ft_is_prompt_line(t, t->c_row - 1))
			t->c_col = t->m_prompt_len;
		t->c_col += t->nl_addr[t->c_row] - t->nl_addr[t->c_row - 1];
		row--;
	}
	t->index--;
	ft_setcursor(--t->c_col, row);
}

void	ft_arrow_input(t_term *t)
{
	static ssize_t	his;

	if (t->ch == 'D' && t->index)
		ft_left(t);
	else if (t->ch == 'C' && t->index < t->bytes)
		ft_right(t);
	else if (t->ch == 'A' && (size_t)his < t->v_history.len)
		ft_history_trigger(t, ++his);
	else if (t->ch == 'B' && his > 0)
		ft_history_trigger(t, --his);
}
