/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_node_delete.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:00:27 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/11 15:05:24 by mbarutel         ###   ########.fr       */
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
