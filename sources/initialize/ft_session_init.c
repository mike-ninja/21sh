/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_session_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:44:03 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/27 21:16:48 by jakken           ###   ########.fr       */
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
//	sesh->tmp_env = NULL;
	sesh->env = ft_env_init();
	sesh->tokens = (t_token *)ft_memalloc(sizeof(*sesh->tokens) * 2);
}
