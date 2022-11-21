/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyboard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:52:45 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/21 11:16:17 by mbarutel         ###   ########.fr       */
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
