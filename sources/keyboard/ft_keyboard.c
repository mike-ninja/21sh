/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyboard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:52:45 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/29 12:53:18 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

int	ft_keyboard(t_term *t)
{
	int	ret;

	ft_init(t);
	ret = ft_input_cycle(t);
	ft_putchar('\n');
	return (ret);
}
