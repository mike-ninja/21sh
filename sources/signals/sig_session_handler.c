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
	// if (num == SIGTERM)
	// {
	// 	ft_printf("SIGTERM\n");
	// 	ft_exit(g_session, 0);
	// }
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
	else if (num == SIGINT)
	{
		kill(g_session->process->pid, SIGINT);
		g_session->process->status = pid_status(g_session->process->pid);
		ft_printf("STATUS: %d\n", g_session->process->status);
	}
	else if (num == SIGTSTP)
	{
		t_proc *ptr = g_session->process;

		while (ptr)
		{
			if (ptr->job == '+')
			{
				ft_putchar('\n');
				// ptr->status = SUSPENDED;	
				display_process_node(ptr);
				kill(ptr->pid, SIGSTOP);
				ptr->status = pid_status(ptr->pid);
				ft_printf("STATUS: %d\n", ptr->status);
			}
			ptr = ptr->next;
		}
	}
	else if (num == SIGSTOP)
	{
		kill(g_session->process->pid, SIGSTOP);
	}
	// else if (num == SIGCONT)
	// 	kill(g_session->process->pid, SIGCONT);
}

void	sigwinc_wait_handle(int num)
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
