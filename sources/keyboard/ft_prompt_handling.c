/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:05:11 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/21 18:25:48 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * If the quote character is not set, set it to the character passed in.
 * If the quote character is set, and the character passed in is the same as
 * the quote character, unset the quote character.
 * 
 * @param t the term structure
 * @param ch the character that was just typed
 */
void	ft_quote_handling(t_term *t, char ch)
{
	if (!t->q_qty || (t->q_qty % 2 && !t->quote))
	{
		t->quote = ch;
		t->q_qty++;
	}
	else if (!(t->q_qty % 2) && !t->quote)
	{
		t->quote = ch;
		t->q_qty++;
	}
	else if (ch == t->quote)
	{
		t->quote = 0;
		t->q_qty++;
	}
}

/**
 * If the character is a backslash, and the index is at the end of the input,
 * then check if the number of backslashes is odd or even. If odd, set the
 * slash flag to 1. If even, set the slash flag to 0.
 * 
 * @param t The structure that holds all the information about the current
 * state of the terminal.
 */
void	ft_slash_handling(t_term *t)
{
	ssize_t	i;

	i = t->index - 1;
	if (t->ch == '\\' && t->index == t->bytes)
	{
		while (i && t->inp[i] == '\\')
			i--;
		if ((t->index - i) % 2)
			t->slash = 1;
		else
			t->slash = 0;
	}
	else
		if (t->ch != D_QUO && t->ch != S_QUO)
			t->slash = 0;
}

/**
 * If the quote quantity is even, then the quote is set to the character at the
 * index minus the number of characters to move back. If the quote quantity is
 * odd and the quote is equal to the character at the index minus the number of
 * characters to move back, then the quote is set to zero.
 * 
 * @param t the term structure
 * @param num the number of characters to be deleted
 */
void	ft_quote_decrement(t_term *t, int num)
{
	if (!(t->q_qty % 2))
	{	
		t->quote = t->inp[t->index - num];
		t->q_qty--;
	}
	else if ((t->q_qty % 2) && t->quote == t->inp[t->index - num])
	{
		t->quote = 0;
		t->q_qty--;
	}
}
