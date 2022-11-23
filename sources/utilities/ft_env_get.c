/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:51:34 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/23 14:52:22 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char	**ft_env_get(t_session *sesh, char *key)
{
	char	**env;
	char	*key_full;

	env = sesh->env;
	key_full = ft_strjoin(key, "=");
	while (*env)
	{
		if (ft_strnequ(*env, key_full, ft_strlen(key_full)))
		{
			ft_strdel(&key_full);
			return (env);
		}
		env++;
	}
	ft_strdel(&key_full);
	return (NULL);
}
