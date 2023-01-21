/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_node_create.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 22:10:49 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/20 19:24:02 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
  Initialise process list - DONE
  functions that inits || appends
  function that deletes node from any position
  dont wait on the child process if does not contain &
  if & sign is present. Fetch the process ID of child process
  jobs:
  if pid still processing then it is running.
  if pid is complete, then display done -> delete node
  man 2 pause() -> pauses a signal
  man 2 kill() -> to check if process is still running

*/
static t_proc *create_node(t_session *sesh, int index, char **args, int pid, t_proc *prev)
{
	int		i;
	t_proc	*ret;

	ret = (t_proc *)ft_memalloc(sizeof(t_proc));
	ret->pid = pid;
	ret->status = 3; // starts the status as running
	ret->index = index;
	ft_memmove(&sesh->process_queue[1], \
	&sesh->process_queue[0], (sesh->process_count - 1) * sizeof(int));
	sesh->process_queue[0] = index;
	ret->next = NULL;
	ret->prev = prev;
	ret->command = (char **)ft_memalloc(sizeof(char *) * (ft_arrlen(args) + 1));
	i = -1;
	while (args[++i])
		ret->command[i] = ft_strdup(args[i]);
	ret->command[i] = NULL;
	return (ret);
}

static int	process_node_append(t_session *sesh, char **args, int pid)
{
	t_proc 	*ptr;
	t_proc 	*prev;

	ptr = sesh->process;
	prev = ptr;
	while (ptr->next)
	{
		prev = ptr;
		ptr = ptr->next;
	}
	ptr->next =	create_node(sesh, ptr->index + 1, args, pid, prev);
	return (ptr->next->index);
}

int process_node_create(char **args, t_session *sesh, int pid)
{
	sesh->process_count++;
	if (!sesh->process)
	{
		sesh->process = create_node(sesh, 1, args, pid, NULL);
		return (sesh->process->index);
	}
	else
		return (process_node_append(sesh, args, pid));
}
