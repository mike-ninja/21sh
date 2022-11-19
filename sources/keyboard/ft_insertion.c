/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insertion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 07:56:09 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/19 12:00:33 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	ft_shift_insert(t_term *t)
{
	ssize_t	bytes_cpy;

	bytes_cpy = t->bytes;
	while (&t->inp[bytes_cpy] >= &t->inp[t->index])
	{
		t->inp[bytes_cpy] = t->inp[bytes_cpy] ^ t->inp[bytes_cpy + 1];
		t->inp[bytes_cpy + 1] = t->inp[bytes_cpy] ^ t->inp[bytes_cpy + 1];
		t->inp[bytes_cpy] = t->inp[bytes_cpy] ^ t->inp[bytes_cpy + 1];
		bytes_cpy--;
	}
}

static void	ft_scroll_down(void)
{
	ft_run_capability("sc");
	ft_run_capability("sf");
	ft_run_capability("rc");
	ft_run_capability("up");
}

static void	ft_trigger_nl(t_term *t)
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
			ft_add_nl_mid_row(t, row + 1, (ssize_t)(&t->nl_addr[row + 1][-1] - t->nl_addr[0]));
	if (t->c_col == t->ws_col)
	{
		t->c_row++;
		t->c_col = 0;
		ft_setcursor(t->c_col, ft_get_linenbr() + 1);
	}
}

void	ft_insertion(t_term *t)
{
	if (t->ch == ENTER)
	{
		if (!t->nl_addr[t->c_row + 1])
		{
			if (t->inp[t->bytes - 1] == '\\' || t->q_qty % 2)
			{
				t->inp[t->bytes++] = (char)t->ch;
				ft_create_prompt_line(t, t->bytes);
				t->index = t->bytes;
			}
		}
	}
	else
	{
		ft_putc(t->ch);
		if (t->ch == D_QUO || t->ch == S_QUO)
			if (!t->index || t->inp[t->index - 1] != '\\')
				ft_quote_handling(t, (char)t->ch);
		t->c_col++;
		ft_shift_nl_addr(t, 1);
		if (t->inp[t->index])
			ft_shift_insert(t);
		t->inp[t->index++] = (char)t->ch;
		t->bytes++;
	}
	ft_trigger_nl(t);
	if (t->inp[t->index])
		ft_print_trail(t);
}
