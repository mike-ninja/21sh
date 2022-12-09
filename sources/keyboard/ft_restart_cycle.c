/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_restart_cycle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:56:42 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/07 11:49:54 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It resets the terminal
 * to its initial state
 *
 * @param t the term structure
 */
void	ft_restart_cycle(t_term *t)
{
	if (t->ch != CTRL_L)
		ft_putendl_fd(t->inp, STDOUT_FILENO);
	ft_memset(t->inp, '\0', BUFFSIZE);
	t->quote = 0;
	t->q_qty = 0;
	t->bytes = 0;
	t->index = 0;
	t->heredoc = 0;
	t->c_col = t->prompt_len;
	t->start_row = ft_get_linenbr();
	t->total_row = 0;
	t->his = 0;
	t->c_row = t->total_row;
	ft_add_nl_last_row(t, t->inp, 0);
	ft_strdel(&t->delim);
	write(1, PROMPT, (size_t)t->prompt_len);
	ft_setcursor(t->c_col, t->c_row + t->start_row);
}
