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
		return (process_getpid(0, NULL, '+', head));
	if (!ft_strcmp("%-", cmd))
		return (process_getpid(0, NULL, '-', head));
	if (*cmd == '%')
		cmd++;
	if (ft_isdigit(*cmd))
		return (process_getpid(ft_atoi(cmd), NULL, 0, head));
	else
		return (process_getpid(0, cmd, 0, head));
	return (NULL);
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
		kill(process->pid, SIGCONT);
		waitpid(process->pid, &status, WUNTRACED);
		if (status & 0177)
			ft_putchar('\n');
	}
	return (0);
}
