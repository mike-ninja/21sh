/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:12:50 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/17 13:04:02 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	env_check_access(char *cmd, char **args)
{
	struct stat	buf;

	if (!cmd || !ft_strchr(cmd, '/'))
	{
		ft_err_print(NULL, args[0], "No such file or directory", 2);
		return (0);
	}
	stat(cmd, &buf);
	if (S_ISDIR(buf.st_mode) || access(cmd, X_OK) == -1)
	{
		ft_err_print(cmd, NULL, "Permission denied", 2);
		return (0);
	}
	return (1);
}

static void	ft_env_execve(char **args, char ***environ_cp)
{
	char	*cmd;

	if (!check_if_user_exe(args[0], &cmd))
		cmd = search_bin(args[0], *environ_cp);
	if (env_check_access(cmd, args) && fork_wrap() == 0)
	{
		if (!cmd || execve(cmd, args, *environ_cp) < 0)
			exe_fail(&cmd, args, environ_cp);
		exit (1);
	}
	ft_strdel(&cmd);
	wait (0);
}

int	ft_env(t_session *sesh, char ***cmd)
{
	int	i;

	i = 1;
	if (*((*cmd) + i) && ft_strchr(*((*cmd) + i), '='))
		i = ft_env_temp(sesh, *cmd, i);
	if (*((*cmd) + i))
	{
		ft_env_execve((*cmd + i), &sesh->env);
		return (0);
	}
	i = -1;
	while (*(sesh->env + ++i))
		ft_putendl(*(sesh->env + i));
	return (0);
}
