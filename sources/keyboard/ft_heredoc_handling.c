/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_handling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 12:57:40 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/09 09:26:59 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It checks if the user is
 * currently typing a heredoc, and if so, it sets the `t->heredoc` variable to 1
 *
 * @param t the term structure
 */
void	ft_heredoc_handling(t_term *t, char ch, int index)
{
	if (index >= 1 && ch == '<' && !(t->q_qty % 2))
	{
		if (t->inp[index - 1] == '<')
		{
			if (index > 2 && t->inp[t->index - 2] == '<')
				t->heredoc = 0;
			else
				t->heredoc = 1;
		}
		else
			t->heredoc = 0;
	}
}
