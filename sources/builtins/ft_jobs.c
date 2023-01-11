/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:58:00 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/11 16:26:04 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	ft_jobs(t_session *sesh)
{
	int		state;
	t_proc	*prev;
	t_proc 	*curr;

	prev = NULL;
	curr = sesh->process_ls;
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
			curr = process_node_delete(prev, curr);
			if (!curr)
				sesh->process_ls = NULL;
		}
		if (curr)
		{
			prev = curr;
			curr = curr->next;
		}
		ft_printf("\n");
	}
	return (0);
}
