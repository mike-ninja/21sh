/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:58:00 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/10 11:43:32 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static t_proc *delete_process_node(t_proc *prev, t_proc *curr)
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

static void display_command(char **cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		ft_printf("%s", cmd[i]);
		if (cmd[i + 1])
			ft_printf(" ");
	}
}

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
		if (!curr->next)
			ft_printf("%c", '+');
		else if (curr->next && !curr->next->next)
			ft_printf("%c", '-');
		else
			ft_printf("%c", ' ');
		// ft_printf(" {%d} ", curr->pid);
		if (state)
			ft_printf("%2s%-24s", "", "Running");
		else
			ft_printf("%2s%-24s", "", "Done");
		display_command(curr->command);
		if (state <= 0)
		{
			curr = delete_process_node(prev, curr);
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
