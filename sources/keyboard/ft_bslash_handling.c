/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bslash_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:28:08 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/11 20:51:45 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * It checks if the last character is a backslash, and if it is, it checks if
 * it's escaped or not.
 * 
 * @param t the structure that holds all the information about the terminal
 */
void	ft_bslash_handling(t_term *t)
{
	ssize_t	i;

	i = t->bytes - 1;
	// if (t->c_row == t->total_row)
	// {
	if (t->inp[i] == '\\' && !t->heredoc)
	{
		i--;
		while (i && t->inp[i] == '\\')
			i--;
		if ((t->bytes - i) % 2)
			t->bslash = 0;
		else
			t->bslash = 1;
	}
	else
		if (t->inp[i] != D_QUO && t->inp[i] != S_QUO)
			t->bslash = 0;
	// }
}
