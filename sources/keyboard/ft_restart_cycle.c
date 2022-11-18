/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_restart_cycle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:20:24 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/18 17:21:56 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	ft_restart_cycle(t_term *t)
{
	ft_putchar('\n');
	ft_printf("{yel}${gre}>{nor} ");
	// ft_memset(t->inp, '\0', BUFFSIZE);
	ft_strclr(t->inp);
	t->quote = 0;
	t->q_qty = 0;
	t->bytes = 0;
	t->index = 0;
	t->c_col = t->prompt_len;
	t->start_row = ft_get_linenbr();
	t->total_row = 0;
	t->c_row = t->total_row;
	ft_add_nl_last_row(t, 0);
	ft_setcursor(t->c_col, t->c_row + t->start_row);
}
