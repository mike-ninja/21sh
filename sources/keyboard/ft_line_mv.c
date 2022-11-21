/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_mv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:16:40 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/21 11:16:53 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static ssize_t	ft_mv_prompt_len(t_term *t, int num)
{
	ssize_t	prompt_len;

	prompt_len = 0;
	if (t->c_row == 1 && (num < 0))
		prompt_len = t->prompt_len;
	else if (ft_is_prompt_line(t, t->c_row + num))
		prompt_len = t->m_prompt_len;
	return (prompt_len);
}

static void	ft_line_down(t_term *t)
{
	ssize_t	len;
	ssize_t	prompt_len;

	prompt_len = ft_mv_prompt_len(t, 1);
	if (t->c_row < (t->total_row - 1))
		len = (t->nl_addr[t->c_row + 2] - t->nl_addr[t->c_row + 1]);
	else
		len = &t->inp[t->bytes] - t->nl_addr[t->c_row + 1];
	if (t->c_col < (len + prompt_len))
	{
		if (t->c_col < prompt_len)
		{
			t->c_col = prompt_len;
			t->index = t->nl_addr[t->c_row + 1] - t->nl_addr[0];
		}
		t->index = &t->nl_addr[t->c_row + 1][t->c_col - prompt_len]
			- t->nl_addr[0];
	}
	else
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
	t->c_row++;
	ft_setcursor(t->c_col, (ft_get_linenbr() + 1));
}

static void	ft_line_up(t_term *t)
{
	ssize_t	len;
	ssize_t	prompt_len;

	len = t->nl_addr[t->c_row] - t->nl_addr[t->c_row - 1];
	prompt_len = ft_mv_prompt_len(t, -1);
	if (t->c_col < (len + prompt_len))
	{
		if (t->c_col < prompt_len)
		{
			t->c_col = prompt_len;
			if (t->c_row == 1)
				t->index = 0;
			else
				t->index = t->nl_addr[t->c_row - 1] - t->nl_addr[0];
		}
		else
			t->index = (&t->nl_addr[t->c_row - 1]
				[t->c_col - prompt_len] - t->nl_addr[0]);
	}
	else
	{
		t->c_col = (len + prompt_len) - 1;
		t->index = (t->nl_addr[t->c_row] - t->nl_addr[0]) - 1;
	}
	t->c_row--;
	ft_setcursor(t->c_col, (ft_get_linenbr() - 1));
}

void	ft_line_mv(t_term *t)
{
	t->ch = ft_get_input();
	if (t->ch == 59)
	{
		t->ch = ft_get_input();
		if (t->ch == 51)
		{
			t->ch = ft_get_input();
			if (t->ch == 65 && t->c_row && ft_get_linenbr())
				ft_line_up(t);
			if (t->ch == 66 && t->c_row < t->total_row)
				ft_line_down(t);
			t->ch = 0;
		}
	}
}
