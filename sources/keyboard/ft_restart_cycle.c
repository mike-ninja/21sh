/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_restart_cycle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:56:42 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/12 15:12:26 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It resets the terminal
 * to its initial state
 *
 * @param t the term structure
 */
// void	ft_restart_cycle(t_term *t)
// {
// 	if (t->ch != CTRL_L)
// 		ft_putendl_fd(t->inp, STDOUT_FILENO);
// 	ft_memset(t->inp, '\0', BUFFSIZE);
// 	t->bslash = 0;
// 	t->quote = 0;
// 	t->q_qty = 0;
// 	t->bytes = 0;
// 	t->index = 0;
// 	t->heredoc = 0;
// 	t->c_col = t->prompt_len;
// 	t->start_row = ft_get_linenbr();
// 	t->total_row = 0;
// 	t->his = 0;
// 	t->c_row = t->total_row;
// 	ft_memdel((void **)&t->nl_addr);
// 	ft_add_nl_last_row(t, t->inp, 0);
// 	ft_strdel(&t->delim);
// 	write(1, PROMPT, (size_t)t->prompt_len);
// 	ft_setcursor(t->c_col, t->c_row + t->start_row);
// }
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
	t->start_row = ft_get_linenbr();
	ft_memdel((void **)&t->nl_addr);
	ft_add_nl_last_row(t, t->inp, 0);
	if (ft_get_linenbr() == (t->ws_row - 1))
		ft_run_capability("sf");
	ft_setcursor(t->c_col, ft_get_linenbr() + 1);
	ft_strclr(t->inp);
	ft_printf("{GREEN}");
	t->c_col = write(1, PROMPT, (size_t)t->prompt_len);
	ft_printf("{RESET}");
}
