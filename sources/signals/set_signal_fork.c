/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal_fork.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 09:24:56 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/16 19:46:09 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	child_signals_init(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGWINCH, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGSTOP, SIG_DFL);
}

// static void	parent_signal_init(void)
// {
// 	signal(SIGWINCH, sigchild_handler);
// 	signal(SIGINT, SIG_IGN);	
// 	signal(SIGTSTP, sigchild_handler);	
// 	signal(SIGSTOP, sigchild_handler);	
// }

void	set_signal_fork(int pid)
{
	if (pid == 0)
		child_signals_init();
	// else
	// {
	// 	signal(SIGINT, sigchild_handler);
	// 	signal(SIGWINCH, sigchild_handler);
	// 	signal(SIGTSTP, sigchild_handler);
	// 	signal(SIGSTOP, sigchild_handler);
	// }
	if (pid)
	{
		signal(SIGINT, sigchild_handler);
		signal(SIGWINCH, sigchild_handler);
		signal(SIGTSTP, sigchild_handler);
		signal(SIGSTOP, sigchild_handler);
	}
}
