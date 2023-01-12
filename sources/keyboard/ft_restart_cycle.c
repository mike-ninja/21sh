/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_restart_cycle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:56:42 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/12 11:24:48 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	heredoc_reset(t_term *t)
{
	if (t->delim)
	{
		ft_memcpy(t->history_buff, t->inp, (unsigned long)t->bytes);
		ft_nl_removal(t);
		ft_history_add_command(t, t->history_buff);
		ft_strdel(&t->delim);
	}
	t->heredoc = 0;
}

/*
 * It resets the terminal
 * to its initial state
 *
 * @param t the term structure
 */

void	ft_restart_cycle(t_term *t)
{
	heredoc_reset(t);
	t->ch = 0;
	t->his = 0;
	t->c_col = 0;
	t->quote = 0;
	t->q_qty = 0;
	t->bytes = 0;
	t->index = 0;
	t->bslash = 0;
	t->total_row = 0;
	t->history_row = -1;
	t->c_row = t->total_row;
	if (t->input_cpy)
		ft_strdel(&t->input_cpy);
	ft_memdel((void **)&t->nl_addr);
	ft_add_nl_last_row(t, t->inp, 0);
	ft_strclr(t->inp);
	ft_strclr(t->history_buff);
	t->c_col = t->term_val[0];
	ft_printf("\n{GREEN}");
	t->c_col += write(1, PROMPT, (size_t)t->prompt_len);
	ft_printf("{RESET}");
	// t->term_val[1] = ft_get_linenbr();
	get_term_val(t->term_val);
}
