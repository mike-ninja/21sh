/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insertion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 07:56:09 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/12 13:33:52 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It fetches the delimiter
 * for a heredoc
 *
 * @param t the term structure
 */
static void	ft_delim_fetch(t_term *t)
{
	char	*ptr;
	char	*end_q;

	if (t->heredoc && !t->delim)
	{
		ptr = ft_strchr(t->inp, '<') + 2;
		while (*ptr && ft_isspace(*ptr))
			ptr++;
		if (*ptr)
		{
			end_q = ptr;
			while (*end_q && !ft_isspace(*end_q))
				end_q++;
			t->delim = ft_strsub(ptr, 0, end_q - ptr);
		}
	}
}

/*
 * It inserts a character into the input string
 *
 * @param t the term structure
 */
static void	ft_insertion_char(t_term *t)
{
	ft_putc(t->ch);
	ft_heredoc_handling(t, t->ch, t->index);
	if ((t->ch == D_QUO || t->ch == S_QUO) && !t->heredoc)
	{
		if (!t->bslash)
			ft_quote_handling(t, (char)t->ch);
		else
			t->bslash = 0;
	}
	t->c_col++;
	ft_shift_nl_addr(t, 1);
	if (t->inp[t->index])
		ft_shift_insert(t);
	t->inp[t->index++] = (char)t->ch;
	t->bytes++;
}

/*
 * If the user is not at the end of the line, the function will
 * insert a new line.
 *
 * @param t the term structure
 */
static void	ft_insertion_enter(t_term *t)
{
	if (!t->nl_addr[t->c_row + 1])
	{
		if (t->bslash || t->q_qty % 2 || (t->heredoc \
			&& (t->delim && ft_strcmp(t->nl_addr[t->c_row], t->delim))))
		{
			t->history_row = -1;
			ft_memcpy(t->history_buff, t->inp, t->bytes);
			t->inp[t->bytes++] = (char)t->ch;
			ft_create_prompt_line(t, t->bytes);
			t->index = t->bytes;
		}
	}
	ft_delim_fetch(t);
}

/*
 * It handles the insertion of characters into the input string
 *
 * @param t the t_term struct
 */
void	ft_insertion(t_term *t)
{
	if (t->ch == ENTER)
		ft_insertion_enter(t);
	else
		ft_insertion_char(t);
	ft_trigger_nl(t);
	if (t->inp[t->index])
		ft_print_trail(t);
}
