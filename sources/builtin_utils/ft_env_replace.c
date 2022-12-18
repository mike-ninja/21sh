/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 12:12:18 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/18 15:41:10 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

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
		if (tmp_env)
			*tmp_env = *envp;
		else
			ft_strdel(envp);
		*envp = ft_strdup(envn);
		ret = 1;
	}
	ft_strdel(&key);
	return (ret);
}
