/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 09:38:04 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/23 19:07:41 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It prints the history of the shell
 *
 * @param t the terminal structure
 */
int	ft_history(t_term *t)
{
	size_t	num_incr;

	num_incr = 0;
	while (++num_incr < t->v_history.len)
		ft_printf("%4d  %s\n", num_incr, \
		(char *)ft_vec_get(&t->v_history, num_incr - 1));
	return (0);
}
