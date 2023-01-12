/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 09:38:04 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/12 18:19:32 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
 * It prints the history of the shell
 *
 * @param t the terminal structure
 */
int	ft_history(t_term *t)
{
	int		i;

	i = 0;
	while (t->history_arr[i])
	{
		ft_printf("%4d %s\n", i, t->history_arr[i]);
		i++;
	}
	return (0);
}
