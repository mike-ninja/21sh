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
	t_proc	*prev;
	t_proc 	*curr;

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
			process_node_delete_v3(prev, &curr);
			if (!prev)
				sesh->process = curr;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
		ft_printf("|\n");
	}
	return (0);
}
// int	ft_jobs(t_session *sesh)
// {
// 	int		state;
// 	t_proc	*prev;
// 	t_proc 	*curr;

// 	prev = NULL;
// 	curr = sesh->process;
// 	while (curr)
// 	{
// 		state = pid_status(curr->pid);
// 		ft_printf("[%d]", curr->index);
// 		ft_printf("%c", curr->job);
// 		if (state)
// 			ft_printf("%2s%-24s", "", "Running");
// 		else
// 			ft_printf("%2s%-24s", "", "Done");
// 		ft_print_dbl_array(curr->command);
// 		if (state <= 0)
// 		{
// 			process_node_delete_v3(prev, &curr);
// 		}
// 		else
// 		{
// 			prev = curr;
// 			curr = curr->next;
// 		}
// 		ft_printf("\n");
// 	}
// 	return (0);
// }
