/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:12:53 by jakken            #+#    #+#             */
/*   Updated: 2022/12/16 12:36:33 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	check_if_user_exe(char *cmd, char **dest)
{
	*dest = NULL;
	if (ft_strchr(cmd, '/'))
	{
		*dest = ft_strdup(cmd);
		return (1);
	}
	return (0);
}

int	check_access(char *cmd, char **args)
{
	struct stat	buf;

	if (!cmd || !ft_strchr(cmd, '/'))
	{
		ft_err_print(NULL, args[0], "command not found", 2);
		return (0);
	}
	stat(cmd, &buf);
	if (S_ISDIR(buf.st_mode))
	{
		ft_err_print(cmd, NULL, "is a directory", 2);
		return (0);
	}
	return (1);
}

void	execute_bin(char **args, char ***environ_cp, t_session *sesh)
{
	char	*cmd;
	int		status;

	status = 0;
	if (!args[0])
		return ;
	if (!ft_builtins(sesh, &args))
		return ;
	if (!check_if_user_exe(args[0], &cmd))
		cmd = search_bin(args[0], *environ_cp);
	if (check_access(cmd, args) && fork_wrap() == 0)
	{
		if (!cmd || execve(cmd, args, *environ_cp) < 0)
			exe_fail(&cmd, args, environ_cp);
		exit (1);
	}
	wait (&status);
	if (WTERMSIG(status))
		ft_putchar('\n');
	ft_memdel((void **)&cmd);
}
