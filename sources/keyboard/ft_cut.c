/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:06:06 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/15 13:14:49 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It cuts the word before the cursor to the clipboard
 *
 * @param t the term structure
 *
 * @return A string that is a copy of the string pointed to by s, but only
 * up to n characters long.
 */
static char	*cut_to_clipboard(t_term *t)
{
	ssize_t	i;
	ssize_t	start;

	i = t->index - 1;
	while (i && ft_isspace(t->inp[i]))
		i--;
	while (i && !ft_isspace(t->inp[i]))
		i--;
	if (!i)
		start = 0;
	else
		start = 1;
	return (ft_strsub(&t->inp[i], start, (size_t)((t->index - i) + 1)));
}

/*
 * It cuts the current line from the cursor position to the end of the line,
 * and stores it in the
 * clipboard
 *
 * @param t The term structure
 */
void	ft_cut(t_term *t)
{
	int	i;

	if (t->bytes)
	{
		i = -1;
		ft_run_capability("vi");
		if (t->clipboard.buff)
			ft_strdel(&t->clipboard.buff);
		t->clipboard.buff = cut_to_clipboard(t);
		while (t->clipboard.buff[++i])
			ft_backspace(t);
		if (t->inp[t->index])
			ft_print_trail(t);
		t->clipboard.type = CUT;
		ft_run_capability("ve");
	}
}
