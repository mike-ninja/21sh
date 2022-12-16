/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_handling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 12:57:40 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/16 13:42:21 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It checks if the user is
 * currently typing a heredoc, and if so, it sets the `t->heredoc` variable to 1
 *
 * @param t the term structure
 */
void	ft_heredoc_handling(t_term *t, int index)
{
	ssize_t	start;
	ssize_t	count;

	start = index;
	while (start && t->inp[start] == '<')
		start--;
	if (start)
		start++;
	count = start;
	while (count < t->bytes && t->inp[count] == '<')
		count++;
	if ((count - start) == 2)
		t->heredoc = 1;
	else
		t->heredoc = 0;
}
