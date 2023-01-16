/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_node_delete.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 22:10:49 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/16 16:59:42 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/**
 * It deletes a node from the linked list and points curr to the next node and
 * if there is a previous node, then they are connected.
 * 
 * @param prev the previous node in the linked list
 * @param curr the current node
 */
void	process_node_delete(t_proc *prev, t_proc **curr)
{
	int		i;
	t_proc	*next;

	i = -1;
	next = (*curr)->next;
	while ((*curr)->command[++i])
		ft_strdel(&(*curr)->command[i]);
	ft_memdel((void **)&(*curr)->command);
	ft_memdel((void **)&(*curr));
	if (prev)
		prev->next = next;
	(*curr) = next;
}
