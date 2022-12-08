/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:12:53 by jakken            #+#    #+#             */
/*   Updated: 2022/12/08 17:01:09 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void exe_cmd_err(char *msg, char *cmd)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

int	ft_freeda(void ***a, size_t row)
{
	unsigned int	i;

	i = -1;
	if (!a)
		return (1);
	while ((*a)[++i] && i < row)
		ft_strdel((char **)&(*a)[i]);
	ft_memdel((void **)a);
	return (1);
}

size_t	calc_chptr(char **arr)
{
	size_t	i;

	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
		++i;
	return (i);
}

int	ms_exit(char **args, char ***environ_cp)
{
	int	status;

	status = 0;
	if (args[1])
		status = ft_atoi(args[1]);
	ft_freeda((void ***)&args, calc_chptr(args));
	ft_freeda((void ***)environ_cp, calc_chptr(*environ_cp));
	exit (status);
}

static void	exe_fail(char **cmd, char **args, char ***env_cp)
{
	exe_cmd_err("command not found", args[0]);
//	ft_printf("minishell: %s: command not found...\n", args[0]);
	ft_memdel((void **)cmd);
	ms_exit(args, env_cp);
}

static int	check_if_user_exe(char *cmd, char **dest)
{
	*dest = NULL;
	if (ft_strchr(cmd, '/'))
	{
		*dest = ft_strdup(cmd);
		return (1);
	}
	return (0);
}

static int	check_access(char *cmd, char **args)
{
	struct stat	buf;

	if (!cmd || !ft_strchr(cmd, '/'))
	{
		exe_cmd_err("command not found", args[0]);
//		ft_printf("minishell: %s: command not found...\n", args[0]);
		return (0);
	}
	stat(cmd, &buf);
	if (S_ISDIR(buf.st_mode))
	{
		exe_cmd_err("is a directory", cmd);
//		ft_printf("minishell: %s: is a directory\n", cmd);
		return (0);
	}
	return (1);
}

void	execute_bin(char **args, char ***environ_cp, t_session *sesh)
{
	char	*cmd;

	if (!args[0])
		return ;
	if (!ft_builtins(sesh, args))
		return ;
	if (!check_if_user_exe(args[0], &cmd))
		cmd = search_bin(args[0], *environ_cp);
	if (check_access(cmd, args) && fork_wrap() == 0)
	{
		if (!cmd || execve(cmd, args, *environ_cp) < 0)
			exe_fail(&cmd, args, environ_cp);
		exit (1);
	}
	wait (0);
	ft_memdel((void **)&cmd);
}
