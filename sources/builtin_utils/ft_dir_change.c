/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dir_change.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 10:57:49 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/30 10:37:50 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	swap_pwd(t_session *sesh, char *cwd)
{
	char	**pwd;
	char	*new_pwd;

	pwd = ft_env_get(sesh, "PWD");
	new_pwd = ft_strjoin("PWD=", cwd);
	if (pwd)
	{
		ft_strdel(pwd);
		*pwd = new_pwd;
	}
	else
	{
		ft_env_append(sesh, &new_pwd);
		ft_strdel(&new_pwd);
	}
}

static void	swap_oldpwd(t_session *sesh)
{
	char	**pwd;
	char	**oldpwd;

	pwd = ft_env_get(sesh, "PWD");
	oldpwd = ft_env_get(sesh, "OLDPWD");
	if (oldpwd && pwd)
	{
		ft_strdel(oldpwd);
		*oldpwd = ft_strjoin("OLDPWD", ft_strchr(*pwd, '='));
	}
}

void	ft_dir_change(t_session *sesh)
{
	char	*oldpwd;
	char	cwd[BUFF_SIZE];

	oldpwd = "OLDPWD=";
	if (!ft_env_get(sesh, "OLDPWD"))
		ft_env_append(sesh, &oldpwd);
	swap_oldpwd(sesh);
	swap_pwd(sesh, getcwd(cwd, sizeof(cwd)));
}
