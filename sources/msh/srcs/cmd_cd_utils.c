/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:13:00 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/13 16:18:59 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap_oldpwd(t_session *sesh)
{
	int		i;
	char	**env;
	char	**pwd;

	i = 0;
	pwd = env_get_var(sesh, "PWD");
	env = env_get_var(sesh, "OLDPWD");
	if (env && pwd)
	{
		ft_strdel(env);
		while (pwd[0][i] != '=')
			i++;
		*env = ft_strjoin("OLDPWD=", &pwd[0][++i]);
	}
}

static void	swap_pwd(t_session *sesh, char *cwd)
{
	char	**env;
	char	*new_pwd;

	new_pwd = ft_strjoin("PWD=", cwd);
	env = env_get_var(sesh, "PWD");
	if (env)
	{
		ft_strdel(env);
		*env = new_pwd;
	}
	else
	{
		append_env(sesh, &new_pwd);
		ft_strdel(&new_pwd);
	}
}

void	cd_success(t_session *sesh)
{
	char	*oldpwd;
	char	cwd[MAXPATHLEN];

	oldpwd = "OLDPWD=";
	if (!env_get_var(sesh, oldpwd))
		append_env(sesh, &oldpwd);
	swap_oldpwd(sesh);
	swap_pwd(sesh, getcwd(cwd, sizeof(cwd)));
}
