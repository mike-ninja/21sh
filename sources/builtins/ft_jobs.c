/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:58:00 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/16 13:40:50y mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	ft_jobs(t_session *sesh)
{
	int		state;
	t_proc 	*curr;

	curr = sesh->process; 
	while (curr)
	{
		state = pid_status(curr->pid);
		if (!state)
			curr->status = EXITED;
		display_process_node(curr);
		if (state <= 0)
			process_node_delete(sesh, &curr);
		else
			curr = curr->next;
	}
	return (0);
}
