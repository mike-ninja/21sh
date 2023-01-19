/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal_fork.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 09:24:56 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/19 12:18:59 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	child_signals_init(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGWINCH, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGSTOP, SIG_DFL);
	signal(SIGCHLD, SIG_IGN);
}

void	set_signal_fork(int pid)
{
	
	if (pid == 0)
		child_signals_init();
	if (pid)
	{
		signal(SIGINT, sigchild_handler);
		signal(SIGWINCH, sigchild_handler);
		signal(SIGTSTP, sigchild_handler);
		signal(SIGSTOP, sigchild_handler);
	}
}
