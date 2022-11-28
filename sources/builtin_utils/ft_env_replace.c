/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 12:12:18 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/26 20:27:15 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

// bool	ft_env_replace(t_session *sesh, char *arg, char **tmp_env)
// {
// 	int		i;
// 	char	*val;
// 	char	*key;

// 	i = -1;
// 	val = ft_strsep(&arg, "=");
// 	while (sesh->env[++i])
// 	{
// 		key = ft_strjoin(val, "=");
// 		if (!ft_strncmp(sesh->env[i], key, ft_strlen(key)))
// 		{
// 			if (tmp_env)
// 				*tmp_env = sesh->env[i];
// 			else
// 				ft_strdel(&sesh->env[i]);
// 			sesh->env[i] = ft_strjoin(key, arg);
// 			ft_strdel(&key);
// 			ft_strdel(&val);
// 			return (true);
// 		}
// 		ft_strdel(&key);
// 	}
// 	ft_strdel(&val);
// 	return (false);
// }

int	ft_env_replace(t_session *sesh, char *envn, char **tmp_env)
{
	int		ret;
	char	*key;
	char	**envp;

	ret = 0;
	key = ft_strsub(envn, 0, ft_strchr(envn, '=') - envn);
	envp = ft_env_get(sesh, key);
	if (envp)
	{
		ft_strdel(envp);
		*envp = envn;
		ret = 1;
	}
	ft_strdel(&key);
	return (ret);
}