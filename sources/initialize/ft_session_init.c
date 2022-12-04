/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_session_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:44:03 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/04 20:23:25 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/**
 * It initializes the session struct.
 *
 * @param sesh The session struct.
 */
void	ft_session_init(t_session *sesh)
{
	sesh->ret = 0;
	ft_env_init(sesh);
	sesh->terminal = ttyname(STDOUT_FILENO);
	sesh->head = NULL;
	sesh->tmp_env_key = NULL;
	sesh->tokens = NULL;
}
