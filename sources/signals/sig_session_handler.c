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
	{
		ft_printf("hello sigint\n");
		ft_restart_cycle(g_session->term);
	}
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
}

void child_exit(int num)
{
	int		status;
	t_proc	*ptr;
	pid_t	pid;

	ptr = g_session->process;
	if (num == SIGCHLD)
	{
		pid = waitpid(-1, &status, WNOHANG);
		ft_printf("pid: %d\n", pid);
		ft_printf("1index: %d\n", ptr->index);
		if (pid > 0) // this means that the process is exited, via completion or termination
		{
			while (ptr)
			{
				if (ptr->pid == pid)
				{
					/* if (ptr->index == g_session->process_queue[0])
					{ */
						ft_printf("2index: %d\n", ptr->index);
						process_node_delete(g_session, &ptr);
						break ;
					/* }
					else
						ptr->status = pid_status(status); */

				}
				ptr = ptr->next;
			}
		}
		else //if suspended it goes here
		{
			while (ptr)
			{
				if (ptr->index == g_session->process_queue[0])
				{
					ptr->status = pid_status(status);
					break ;
				}
				ptr = ptr->next;
			}
		}
	}
}
