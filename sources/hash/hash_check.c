/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:11:44 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/10 16:53:42 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char	*hash_check(t_session *sesh, char *program)
{
	int		index;
	t_hash	*tmp;

	index = hash_function(program);
	if (sesh->ht[index])
	{
		tmp = sesh->ht[index];
		while (tmp)
		{
			if (ft_strequ(ft_strrchr(tmp->program, '/' + 1), program))
			{
				return (ft_strdup(tmp->program));
			}
			tmp = tmp->next;
		}
	}
	return (NULL);
}
