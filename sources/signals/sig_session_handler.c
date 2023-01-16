/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_session_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 09:02:29 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/15 20:17:10 by mbarutel         ###   ########.fr       */
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
