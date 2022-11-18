/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:59:54 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/17 10:06:39 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*cd_get_expansion(t_session *sesh)
{
	char	**env;

	env = NULL;
	if (array_len(sesh->tok->arg, 0) == 1
		|| ft_strcmp(sesh->tok->arg[1], "--") == 0)
	{
		env = env_get_var(sesh, "HOME=");
		if (env)
			return (ft_strdup(ft_strchr(*env, '=') + 1));
	}
	else if (ft_strcmp(sesh->tok->arg[1], "-") == 0)
	{
		env = env_get_var(sesh, "OLDPWD=");
		if (env)
		{
			ft_printf("%s\n", ft_strchr(*env, '=') + 1);
			return (ft_strdup(ft_strchr(*env, '=') + 1));
		}
	}
	return (NULL);
}

static void	chdir_expand(t_session *sesh, char **path)
{
	chdir(*path);
	cd_success(sesh);
	ft_strdel(path);
}

static bool	cd_expansion(t_session *sesh)
{
	char	*path;

	path = cd_get_expansion(sesh);
	if (path)
	{
		chdir_expand(sesh, &path);
		return (RESET);
	}
	if (!sesh->tok->arg[1] || !ft_strcmp(sesh->tok->arg[1], "--"))
	{
		ft_printf("cd: HOME not set\n");
		return (RESET);
	}
	if (!ft_strcmp(sesh->tok->arg[1], "~-")
		|| !ft_strcmp(sesh->tok->arg[1], "-"))
	{
		ft_printf("cd: OLDPWD not set\n");
		return (RESET);
	}
	return (ERROR);
}

int	cmd_cd(t_session *sesh)
{
	if (array_len(sesh->tok->arg, 0) > 2)
	{
		sesh->result = TOOMANYARGS;
		return (sesh->result);
	}
	if (cd_expansion(sesh) == RESET)
		return (RESET);
	sesh->result = check_address(sesh->tok->arg[1]);
	if (sesh->result == RESET)
	{
		if (chdir(sesh->tok->arg[1]) != 0)
		{
			ft_printf("minishell: cd: %s: Not a directory\n", sesh->tok->arg[1]);
			return (RESET);
		}
		else
			cd_success(sesh);
		return (RESET);
	}
	return (sesh->result);
}
