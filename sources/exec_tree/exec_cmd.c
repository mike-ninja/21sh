/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:12:53 by jakken            #+#    #+#             */
/*   Updated: 2023/01/16 19:37:22 by mbarutel         ###   ########.fr       */
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

static int	check_file_validity(struct stat *buff, char *cmd)
{
	if (S_ISDIR(buff->st_mode))
	{
		ft_err_print(NULL, cmd, "Is a directory", 2);
		return (0);
	}
	else if (access(cmd, X_OK) < 0)
	{
		ft_err_print(NULL, cmd, "Permission denied", 2);
		return (0);
	}
	return (1);
}

int	check_access(char *cmd, char **args, t_session *sesh)
{
	struct stat	buf;

	if (((cmd && ft_strchr(cmd, '/')) && access(cmd, F_OK) < 0))
	{
		ft_err_print(NULL, args[0], "No such file or directory", 2);
		sesh->exit_stat = 127;
		return (0);
	}
	else if (!cmd || !ft_strchr(cmd, '/'))
	{
		if (ft_env_get(sesh, "PATH"))
			ft_err_print(NULL, args[0], "command not found", 2);
		else
			ft_err_print(NULL, args[0], "No such file or directory", 2);
		sesh->exit_stat = 127;
		return (0);
	}
	stat(cmd, &buf);
	if (!check_file_validity(&buf, cmd))
	{
		sesh->exit_stat = 126;
		return (0);
	}
	return (1);
}

void	execute_bin(char **args, char ***environ_cp, t_session *sesh)
{
	char	*cmd;
	int		access;
	int		status;
	pid_t	pid;

	status = 0;
	if (!args[0])
		return ;
	if (!ft_builtins(sesh, &args))
		return ;
	if (!check_if_user_exe(args[0], &cmd))
		cmd = search_bin(args[0], *environ_cp);
	access = check_access(cmd, args, sesh);
	if (cmd && access)
		pid = fork_wrap();
	if (cmd && access)
	{
		if (pid && sesh->process_control)
			ft_printf("[%d] %d\n", process_node_append(args, sesh, pid), pid);
		else if (pid)
			process_node_append(args, sesh, pid);
		// else if (pid == 0 && sesh->process)
		// 	setsid()
	}
	if (access && pid == 0)
	{
		setsid();
		if (!cmd || execve(cmd, args, *environ_cp) < 0)
			exe_fail(&cmd, args, environ_cp);
		exit (1);
	}
	if (cmd && access && sesh->process_control == 0)
	{
		// wait(&status);
		waitpid(pid, &status, WUNTRACED);

		if (WIFEXITED(status))
		{	
			t_proc *ptr = sesh->process;
			t_proc *prev;

			prev = NULL;
			while (ptr)
			{
				if (ptr->pid == pid)
				{
					process_node_delete(prev, &ptr);
					if (!prev)
						sesh->process = ptr;
					break ;
				}
				else
				{
					prev = ptr;
					ptr = ptr->next;
				}
			}
		}
	}
	if (status & 0177)
		ft_putchar('\n');
	if (access)
		sesh->exit_stat = status >> 8;
	ft_memdel((void **)&cmd);
}
