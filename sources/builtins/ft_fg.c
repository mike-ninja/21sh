/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:46:44 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/11 15:50:53y mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
	- How does the % work when used as parameter
		- % by itself || %% is same as %+
		- %number is the same as fg number
*/
/*
	Args can be:
		- index
		- process name, but only if there is only one
*/

static t_proc	*fg_parsing(t_proc *head, char *cmd)
{
	if (!cmd || !ft_strcmp("%%", cmd) || !ft_strcmp("%+", cmd))
		return (process_getpid(0, NULL, /* '+', */ head));
	if (!ft_strcmp("%-", cmd))
		return (process_getpid(0, NULL, /* '-', */ head));
	if (*cmd == '%')
		cmd++;
	if (ft_isdigit(*cmd))
		return (process_getpid(ft_atoi(cmd), /* NULL, */ 0, head));
	else
		return (process_getpid(0, cmd, /* 0, */ head));
	return (NULL);
}

static void	update_queue(t_session *sesh, t_proc *process)
{
	int tmp;
	int i;

	i = 0;
	while (i < sesh->process_count)
	{
		if (process->index == sesh->process_queue[0])
			break ;
		else if (process->index == sesh->process_queue[i])
		{
			tmp = sesh->process_queue[i];
			ft_memmove(&sesh->process_queue[1], &sesh->process_queue[0], i * sizeof(int));
			sesh->process_queue[0] = tmp;
			break ;
		}
		i++;
	}
}

int	ft_fg(t_session *sesh, char **cmd)
{
	int		status;
	t_proc	*process;

	process = fg_parsing(sesh->process , *(cmd + 1));
	if (!process)
		ft_printf("fg: no such job\n");
	else
	{
		ft_print_dbl_array(process->command);
		ft_putchar('\n');
		signal(SIGINT, sigchild_handler);
		signal(SIGWINCH, sigchild_handler);
		signal(SIGTSTP, sigchild_handler);
		signal(SIGSTOP, sigchild_handler);
		update_queue(sesh, process);
		// kill(process->pid, SIGCONT);
		ft_printf("fg %d\n", process->pid);
		waitpid(process->pid, &status, WUNTRACED);
		ft_printf("fg %d\n", process->pid);
	}
	return (0);
}
