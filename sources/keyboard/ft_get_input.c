/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 07:52:49 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/29 16:40:50 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It reads one character from the standard input and returns it
 *
 * @return The character that was read from the standard input.
 */
int	ft_get_input(void)
{
	int	c;

	c = 0;
	read(STDIN_FILENO, &c, 1);
	return (c);
}
