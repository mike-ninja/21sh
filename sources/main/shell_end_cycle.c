/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_end_cycle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 14:26:23 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/18 14:03:48 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

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

// static void	delete_completed_process(t_session *sesh)
// {
// 	t_proc *ptr;

// 	ptr = sesh->process;
// 	while (ptr)
// 	{
// 		if (!ptr->status)
// 			ptr->status = pid_status(ptr->pid);
		
// 	}
// }

/**
 * It resets the tokens and sets the return value to 0
 *
 * @param sesh the session struct
 */
void	shell_end_cycle(t_session *sesh)
{
	free_node(sesh->head);
	free_tokens(&sesh->tokens);
	reset_fd(sesh->terminal);
	ft_reset_tmp_env(sesh);
	// delete_completed_process(sesh);
}
