/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 09:38:04 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/09 14:59:08 by mbarutel         ###   ########.fr       */
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
