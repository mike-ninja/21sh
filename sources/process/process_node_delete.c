/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_node_delete.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 22:10:49 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/16 15:29:10 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_proc *process_node_delete(t_proc *prev, t_proc *curr)
{
	int		i;
	t_proc	*next;

	i = -1;
	next = curr->next;
	while (curr->command[++i])
		ft_strdel(&curr->command[i]);
	ft_memdel((void **)&curr->command);
	ft_memdel((void **)&curr);
	if (prev)
	{
		prev->next = next;
		return (prev);
	}
	return (NULL);
}
/*		this updates the prev->next and points the curr to the next node	*/
void	process_node_delete_v3(t_proc *prev, t_proc **curr)
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

void process_node_delete_v2(t_proc **curr)
{
	int		i;
	t_proc	*next;

	i = -1;
	next = (*curr)->next;
	while ((*curr)->command[++i])
		ft_strdel(&(*curr)->command[i]);
	ft_memdel((void **)&(*curr)->command);
	ft_memdel((void **)&(*curr));
	(*curr) = next;
}
