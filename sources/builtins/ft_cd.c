/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:10:09 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/14 13:43:58 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	ft_chdir_expanded(t_session *sesh, char **path)
{
	chdir(*path);
	ft_dir_change(sesh);
	ft_strdel(path);
	return (1);
}

static int	ft_cd_expand_error(char **cmd)
{
	if (!*(cmd + 1) || !ft_strcmp(*(cmd + 1), "--"))
		ft_err_print(NULL, "cd", "HOME not set", 1);
	else if (!ft_strcmp(*(cmd + 1), "~-") || !ft_strcmp(*(cmd + 1), "-"))
		ft_err_print(NULL, "cd", "OLDPWD not set", 1);
	return (1);
}


static int ft_cd_expand(t_session *sesh, char **cmd, char **path)
{
	int		ret;
	char	**env;

	ret = 0;
	if (ft_arrlen(cmd) == 1 || !ft_strcmp(*(cmd + 1), "--"))
	{
		env = ft_env_get(sesh, "HOME");
		if (env)
			*path = ft_strdup(ft_strchr(*env, '=') + 1);
		ret = 1;
	}
	else if (!ft_strcmp(*(cmd + 1), "-"))
	{
		env = ft_env_get(sesh, "OLDPWD");
		if (env)
		{
			ft_putendl(ft_strchr(*env, '=') + 1);
			*path = ft_strdup(ft_strchr(*env, '=') + 1);
		}
		ret = 1;
	}
	if (*path)
		return (ft_chdir_expanded(sesh, path));
	else if (ret || !ft_strcmp(*(cmd + 1), "~-"))
		return (ft_cd_expand_error(cmd));
	return (0);
}

static bool	ft_cd_expand_parse(t_session *sesh, char **cmd)
{
	char	*path;

	path = NULL;
	if (ft_cd_expand(sesh, cmd, &path))
		return (1);
	return (0);
}

int	ft_cd(t_session *sesh, char **cmd)
{
	sesh->exit_stat = 0;
	if (ft_arrlen(cmd) > 2)
		ft_err_print(NULL, "cd", "too many arguments", 1);
	else if (!ft_cd_expand_parse(sesh, cmd) && !ft_cd_addr_check(*(cmd + 1)))
	{
		if (chdir(*(cmd + 1)))
			sesh->exit_stat = 1;
		else
			ft_dir_change(sesh);
	}
	else
		sesh->exit_stat = 1;
	return (0);
}
