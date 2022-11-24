/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_endcycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:00:16 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/24 14:19:45 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/**
 * It resets the tokens array
 * 
 * @param sesh The session struct.
 */
static void	ft_reset_tokens(t_session *sesh)
{
	int	i;

	i = -1;
	while (sesh->tokens[++i].token)
	{
		ft_strdel(&sesh->tokens[i].token);
		ft_strdel(&sesh->tokens[i].value);
	}
	ft_memdel((void **)&sesh->tokens);
	sesh->tokens = (t_token *)ft_memalloc(sizeof(*sesh->tokens) * 2);
}

/**
 * It resets the tokens and sets the return value to 0
 * 
 * @param sesh the session struct
 */
void	ft_endcycle(t_session *sesh)
{
	sesh->ret = 0;
	ft_reset_tokens(sesh);
}
