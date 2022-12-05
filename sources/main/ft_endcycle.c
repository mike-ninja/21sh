/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_endcycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:00:16 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/05 19:26:33 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

// /**
//  * It resets the tokens array
//  *
//  * @param sesh The session struct.
//  */
static void	ft_reset_tokens(t_session *sesh)
{
	int	i;

	i = -1;
	while (sesh->tokens[++i].token)
		ft_strdel(&sesh->tokens[i].value);
	ft_printf("Resetting tokens array\n");
	ft_memdel((void **)&sesh->tokens);
	// sesh->tokens = (t_token *)ft_memalloc(sizeof(*sesh->tokens) * 2);
}

static void	ft_reset_tmp_env(t_session *sesh)
{
	int		i;
	char	*key;
	char	**env;

	i = -1;
	if (sesh->tmp_env_key)
	{
		while (sesh->tmp_env_key[++i])
		{
			key = ft_strchr(sesh->tmp_env_key[i], '=');
			if (key)
			{
				key = ft_strsub(sesh->tmp_env_key[i], 0, key - \
					sesh->tmp_env_key[i]);
				env = ft_env_get(sesh, key);
				ft_strdel(env);
				*env = ft_strdup(sesh->tmp_env_key[i]);
				ft_strdel(&key);
			}
			else
				ft_env_remove(sesh, sesh->tmp_env_key[i]);
			ft_strdel(&sesh->tmp_env_key[i]);
		}
		ft_memdel((void **)&sesh->tmp_env_key);
	}
}

/**
 * It resets the tokens and sets the return value to 0
 *
 * @param sesh the session struct
 */
void	ft_endcycle(t_session *sesh)
{
	sesh->ret = 0;
	if (sesh->head)
		free_node(sesh->head);
	sesh->head = NULL;
	free_tokens(sesh->tokens);
	reset_fd(sesh->terminal);
	ft_reset_tmp_env(sesh);
}
