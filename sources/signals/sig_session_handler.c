/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_session_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 09:02:29 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/17 17:56:53 mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

extern t_session	*g_session;

/*
 * It's a signal handler that
 * handles the window size change and the interrupt signal
 *
 * @param num The signal number.
 */
void	sig_session_handler(int num)
{
	if (num == SIGWINCH)
		ft_window_size(g_session->term);
	if (num == SIGINT)
		ft_restart_cycle(g_session->term);
}

void	sigchild_handler(int num)
{
	struct winsize	size;

	if (num == SIGWINCH)
	{
		if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) < 0)
		{
			ft_putstr_fd("could not get the terminal size", 2);
			exit(1);
		}
		g_session->term->ws_col = size.ws_col;
		g_session->term->ws_row = size.ws_row;
	}
	// else if (num == SIGINT)
	// 	kill(g_session->process->pid, SIGINT);
	// else if (num == SIGTSTP || num == SIGSTOP)
	// {
	// 	t_proc *ptr = g_session->process;

	// 	while (ptr)
	// 	{
	// 		if (ptr->queue == '+')
	// 		{
	// 			ft_putchar('\n');
	// 			kill(ptr->pid, SIGSTOP);
	// 			ptr->status = 1;
	// 			display_process_node(ptr);
	// 		}
	// 		ptr = ptr->next;
	// 	}
	// }
}

// static void	update_queue_back(t_session *sesh, t_proc *process)
// {
// 	t_proc	*ptr;

// 	ptr = sesh->process;
// 	while (ptr)
// 	{
// 		if (ptr == process)
// 			ptr->queue = '+';
// 		else if (ptr->queue == '+')
// 			ptr->queue = '-';
// 		else if (ptr->queue == '-')
// 			ptr->queue = ' ';
// 		ptr = ptr->next;
// 	}
// }

void child_exit(int num) // we need an update queue here
{
	int		status;
	t_proc	*ptr;
	pid_t	pid;

	ptr = g_session->process;
	if (num == SIGCHLD)
	{
		pid = waitpid(-1, &status, WNOHANG);
		if (pid > 0) // this means that the process is exited, via cmpletion or termination
		{
			while (ptr)
			{
				if (ptr->pid == pid)
				{
					if (ptr->ground == true)
						process_node_delete(g_session, &ptr);
					else
						ptr->status = pid_status(status);
					break ;
				}
				ptr = ptr->next;
			}
		}
		else
		{
			while (ptr)
			{
				// if (ptr->queue == '+')
				if (ptr->line == 0)
				{
					ptr->status = pid_status(status);
					break ;
				}
				ptr = ptr->next;
			}
		}
	}
}
