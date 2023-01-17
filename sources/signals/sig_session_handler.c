/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_session_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 09:02:29 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/17 11:04:43 by mbarutel         ###   ########.fr       */
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
		kill(g_session->process->pid, SIGINT);
	else if (num == SIGTSTP)
	{
		ft_printf("SIGTSTP\n");
		kill(g_session->process->pid, SIGSTOP);
	}
	else if (num == SIGSTOP)
	{
		ft_printf("SIGSTOP\n");
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

void	sigstop_handler(int num)
{	
	if (num == SIGTSTP)
	{
		// pid_t pid;

		// pid = getpid();
		// ft_printf("%d", pid);
		// t_proc	*ptr = g_session->process;
		// kill(getpid(), SIGTSTP);
	}
}
