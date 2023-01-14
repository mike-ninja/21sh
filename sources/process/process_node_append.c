/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_node_append.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 22:10:49 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/14 22:47:07 by mbarutel         ###   ########.fr       */
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

static t_proc *create_process_node(int index, char **args, int pid)
{
	int		i;
	t_proc	*ret;

	i = -1;
	ret = (t_proc *)ft_memalloc(sizeof(t_proc));
	ret->index = index;
	ret->pid = pid;
	ret->job = 0;
	ret->next = NULL;
	ret->command = (char **)ft_memalloc(sizeof(char *) * (ft_arrlen(args) + 1));
	while (args[++i])
		ret->command[i] = ft_strdup(args[i]);
	ret->command[i] = NULL;
	return (ret);
}

int process_node_append(char **args, t_session *sesh, int pid)
{
	t_proc 	*ptr;

	ptr = NULL;
	if (!sesh->process)
	{
		sesh->process = create_process_node(1, args, pid);
		// update_precedence(sesh->process, 0);
		return (sesh->process->index);
	}
	else
	{
		ptr = sesh->process;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next =	create_process_node(ptr->index + 1, args, pid); 
		// update_precedence(sesh->process, 0);
		return (ptr->next->index);
	}
} 
