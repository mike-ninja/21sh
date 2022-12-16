/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_restart_cycle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:56:42 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/16 12:14:00 by mbarutel         ###   ########.fr       */
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
	t->ch = 0;
	t->his = 0;
	t->c_col = 0;
	t->quote = 0;
	t->q_qty = 0;
	t->bytes = 0;
	t->index = 0;
	t->bslash = 0;
	t->heredoc = 0;
	t->total_row = 0;
	t->c_row = t->total_row;
	if (t->delim)
		ft_strdel(&t->delim);
	ft_memdel((void **)&t->nl_addr);
	ft_add_nl_last_row(t, t->inp, 0);
	ft_strclr(t->inp);
	ft_printf("\n{GREEN}");
	t->c_col = write(1, PROMPT, (size_t)t->prompt_len);
	ft_printf("{RESET}");
}
