/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_end_cycle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:04:06 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/11 12:43:34 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It's called at the end of the main loop, and it handles the newline
 * character, the history, and the
 * input copy
 *
 * @param t the term struct
 */
void	ft_end_cycle(t_term *t)
{
	if (t->bytes)
	{
		ft_memcpy(t->history_buff, t->inp, (unsigned long)t->bytes);
		ft_nl_removal(t);
		ft_history_add_command(t, t->history_buff);
	}
	ft_memdel((void **)&t->nl_addr);
	if (t->input_cpy)
		ft_strdel(&t->input_cpy);
}
