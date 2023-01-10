/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:12:53 by jakken            #+#    #+#             */
/*   Updated: 2023/01/10 12:22:21 by mbarutel         ###   ########.fr       */
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

/* PROCESS IMPLEMENTATION */
static t_proc *create_process_node(int index, char **args, int pid)
{
	int		i;
	t_proc	*ret;

	i = -1;
	ret = (t_proc *)ft_memalloc(sizeof(t_proc));
	ret->index = index;
	ret->pid = pid;
	ret->status = 0;
	ret->next = NULL;
	ret->command = (char **)ft_memalloc(sizeof(char *) * (ft_arrlen(args) + 1));
	while (args[++i])
		ret->command[i] = ft_strdup(args[i]);
	ret->command[i] = NULL;
	return (ret);
}

static int process_ls_append(char **args, t_session *sesh, int pid)
{
	t_proc 	*ptr;

	ptr = NULL;
	if (!sesh->process_ls)
	{
		sesh->process_ls = create_process_node(1, args, pid);
		return (sesh->process_ls->index);
	}
	else
	{
		ptr = sesh->process_ls;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next =	create_process_node(ptr->index + 1, args, pid); 
		return (ptr->next->index);
	}
} 
/* PROCESS IMPLEMENTATION */

void	execute_bin(char **args, char ***environ_cp, t_session *sesh)
{
	char	*cmd;
	int		access;
	int		status;
	int		pid;

	status = 0;
	if (!args[0])
		return ;
	if (!ft_builtins(sesh, &args))
		return ;
	if (!check_if_user_exe(args[0], &cmd))
		cmd = search_bin(args[0], *environ_cp);
	access = check_access(cmd, args, sesh);
	pid = fork_wrap();
	if (access && pid == 0)
	{
		if (!cmd || execve(cmd, args, *environ_cp) < 0)
			exe_fail(&cmd, args, environ_cp);
		// exit (1);
		exit (0);
	}
	if (!sesh->bg)
		waitpid(pid, &status, 0);
	else if (pid)
	{
		
		// append process ID NODE HERE
		// process_ls_append(args, sesh, pid);
		ft_printf("[%d] %d\n", process_ls_append(args, sesh, pid), pid);
	}
	if (status & 0177)
		ft_putchar('\n');
	if (access)
		sesh->exit_stat = status >> 8;
	ft_memdel((void **)&cmd);
}
