/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:10:49 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/10 13:11:40 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	hash_print(t_hash **ht)
{
	t_hash	*tmp;
	int		i;

	i = -1;
	while (++i < HASH_SIZE)
	{
		if (ht[i])
		{
			ft_printf("hits    command\n");
			break ;
		}
	}
	if (i == HASH_SIZE)
	{
		ft_putstr_fd("21sh: hash table empty\n", 2);
		return ;
	}
	i = -1;
	while (++i < HASH_SIZE)
	{
		if (ht[i] != NULL)
		{
			tmp = ht[i];
			while (tmp != NULL)
			{
				ft_printf("%d	%s\n", tmp->hits, tmp->program);
				tmp = tmp->next;
			}
		}
	}
}
