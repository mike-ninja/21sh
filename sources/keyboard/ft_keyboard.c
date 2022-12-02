/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyboard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:52:45 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/02 20:37:48 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

int	ft_keyboard(t_term *t)
{
	ft_init_term(t);
	ft_input_cycle(t);
	if (t->nl_addr)
		ft_memdel((void **)&t->nl_addr);
	ft_history_write_to_file(t);
	return (0);
}
