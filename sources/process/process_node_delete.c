/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_node_delete.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 22:10:49 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/20 19:20:54 by mrantil          ###   ########.fr       */
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
// void	process_node_delete(t_proc *prev, t_proc **curr)
// {
// 	int		i;
// 	t_proc	*next;

// 	i = -1;
// 	next = (*curr)->next;
// 	while ((*curr)->command[++i])
// 		ft_strdel(&(*curr)->command[i]);
// 	ft_memdel((void **)&(*curr)->command);
// 	ft_memdel((void **)&(*curr));
// 	if (prev)
// 		prev->next = next;
// 	(*curr) = next;
// }

static void	delete_from_queue(t_session *sesh, t_proc *process)
{
	int i;

	i = 0;
	while (i < sesh->process_count)
	{
		if (process->index == sesh->process_queue[i])
		{
			ft_memmove(&sesh->process_queue[i], &sesh->process_queue[i + 1], \
			(sesh->process_count - i) * sizeof(int)); //do we need to have -1 before i here?
			sesh->process_count--;
			break ;
		}
		i++;
	}
}

void	process_node_delete(t_session *sesh, t_proc **curr)
{
	int		i;
	t_proc	*next;

	next = (*curr)->next;
	delete_from_queue(sesh, *curr);
	i = -1;
	while ((*curr)->command[++i])
		ft_strdel(&(*curr)->command[i]);
	ft_memdel((void **)&(*curr)->command);
	ft_memdel((void **)&(*curr));
	(*curr) = next;

}
