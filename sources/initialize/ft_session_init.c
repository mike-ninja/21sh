/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_session_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:44:03 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/20 12:47:02 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_session	*g_session;

/**
 * It initializes the session struct.
 *
 * @param sesh The session struct.
 */
void	ft_session_init(t_session *sesh)
{
	sesh->process = NULL;
	sesh->process_control = 0;
	init_window_size(sesh->term);
	g_session = sesh;
	sesh->exit_stat = 0;
	sesh->process->count = 0;
	sesh->line = NULL;
	ft_env_init(sesh);
	sesh->terminal = ttyname(STDOUT_FILENO);
	sesh->head = NULL;
	sesh->tmp_env_key = NULL;
	sesh->tokens = NULL;
}
