/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_node_delete.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 22:10:49 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/15 20:34:37 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_proc *process_node_delete(t_proc *prev, t_proc *curr)
{
	int		i;
	t_proc	*next;

	i = -1;
	next = NULL;
	while (curr->command[++i])
		ft_strdel(&curr->command[i]);
	ft_memdel((void **)&curr->command);
	if (curr->next)
		next = curr->next;
	ft_memdel((void **)&curr);
	if (prev)
	{
		prev->next = next;
		return (prev);
	}
	else if (next)
		return (next);
	return (NULL);
}
