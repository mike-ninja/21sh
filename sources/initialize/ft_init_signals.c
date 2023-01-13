/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 18:17:16 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/13 10:04:53 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

extern t_session	*g_t;

/*
 * It's a signal handler that
 * handles the window size change and the interrupt signal
 *t_term
 * @param num The signal number.
 */
void	sig_handler(int num)
{	
	if (num == SIGWINCH)
		ft_window_size(g_t->term);
	if (num == SIGINT)
		ft_restart_cycle(g_t->term);
}

/*
 * It initializes the signal handlers for the program
 */
void	ft_init_signals(void)
{
	signal(SIGWINCH, sig_handler);
	signal(SIGINT, sig_handler);
}
