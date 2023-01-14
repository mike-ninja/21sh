/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_node_delete.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 22:10:49 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/14 22:14:04 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_proc *process_node_delete(t_proc *prev, t_proc *curr)
{
	int	i;

	i = -1;
	if (prev)
		prev->next = curr->next;
	while (curr->command[++i])
		ft_strdel(&curr->command[i]);
	ft_memdel((void **)&curr->command);
	ft_memdel((void **)&curr);
	if (prev)
		return (prev);
	return (NULL);
}
