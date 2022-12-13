/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nl_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:00:30 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/09 10:44:19 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * It removes the newline character from the history buffer if it's preceded 
 * by a backslash or if it's the last character in the buffer
 * 
 * @param t the term structure
 */
void	ft_nl_removal(t_term *t)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (t->history_buff[i])
	{
		if (i && t->history_buff[i] == '\n' && (t->history_buff[i - 1] == '\\' \
			|| !t->history_buff[i + 1]))
			i++;
		t->history_buff[j++] = t->history_buff[i++];
	}
}
