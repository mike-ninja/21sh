/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_mv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:43:30 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/04 19:22:12 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It moves the cursor to the beginning of the previous word
 *
 * @param t the term structure
 */
static void	ft_word_left(t_term *t)
{
	while (t->index && ft_isspace(t->inp[t->index - 1]))
	{
		if (&t->inp[t->index + 1] == t->nl_addr[t->c_row])
			break ;
		t->index--;
	}
	while (t->index && !ft_isspace(t->inp[t->index - 1]))
	{
		if (&t->inp[t->index] == t->nl_addr[t->c_row])
			break ;
		t->index--;
	}
	t->c_col = &t->inp[t->index] - t->nl_addr[t->c_row];
	if (t->nl_addr[t->c_row] == &t->inp[0])
		t->c_col += t->prompt_len;
	else if (ft_is_prompt_line(t, t->c_row))
		t->c_col += t->m_prompt_len;
	ft_setcursor(t->c_col, ft_get_linenbr());
}

/*
 * It moves the cursor to the
 * beginning of the next word
 *
 * @param t the term structure
 */
static void	ft_word_right(t_term *t)
{
	ssize_t	row;

	row = t->c_row;
	while (t->index < t->bytes && ft_isspace(t->inp[t->index]))
	{
		if (t->nl_addr[row + 1] && &t->inp[t->index + 1] == t->nl_addr[row + 1])
			break ;
		t->index++;
	}
	while (t->index < t->bytes && !ft_isspace(t->inp[t->index]))
	{
		if (t->nl_addr[row + 1] \
		&& &t->inp[t->index + 1] == t->nl_addr[row + 1])
			break ;
		t->index++;
	}
	t->c_col = &t->inp[t->index] - t->nl_addr[row];
	if (t->nl_addr[row] == &t->inp[0])
		t->c_col += t->prompt_len;
	else if (ft_is_prompt_line(t, row))
		t->c_col += t->m_prompt_len;
	ft_setcursor(t->c_col, ft_get_linenbr());
}

/*
 * If the user presses the alt-left key, and the cursor is not at the beginning
 * of the line, move the cursor to the beginning of the previous word. If the
 * user presses the alt-right key, and the cursor is not at the end of the line,
 * move the cursor to the beginning of the next word
 *
 * @param t the t_term struct
 */
void	ft_word_mv(t_term *t)
{
	if (t->ch == ALT_LFT && (&t->inp[t->index] > t->nl_addr[t->c_row]))
		ft_word_left(t);
	else if (t->ch == ALT_RGHT && (t->index < t->bytes))
		ft_word_right(t);
}
