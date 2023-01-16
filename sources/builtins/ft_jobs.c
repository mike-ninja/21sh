/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:58:00 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/15 20:45:31 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	ft_jobs(t_session *sesh)
{
	int		state;
	t_proc	*prev;
	t_proc 	*curr;
	t_proc 	*next;

	prev = NULL;
	curr = sesh->process;
	while (curr)
	{
		state = pid_status(curr->pid);
		ft_printf("[%d]", curr->index);
		ft_printf("%c", curr->job);
		if (state)
			ft_printf("%2s%-24s", "", "Running");
		else
			ft_printf("%2s%-24s", "", "Done");
		ft_print_dbl_array(curr->command);
		if (state <= 0)
		{
			next = curr->next;
			curr = process_node_delete(prev, curr);
			if (!curr && !next)
				sesh->process = NULL;
		}
		if (curr && curr != next) // problem here
		{
			prev = curr;
			curr = curr->next;
		}
		ft_printf("\n");
	}
	return (0);
}
