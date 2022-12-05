/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_session_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:44:03 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/05 16:44:48 by jniemine         ###   ########.fr       */
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
