/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:14:38 by jakken            #+#    #+#             */
/*   Updated: 2022/12/14 12:40:32 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void open_fd_if_needed(int fd, char *terminal)
{
	struct stat	buf;
	int			closefd[3];
	int			i;

	ft_bzero((void *)closefd, sizeof(closefd));
	i = 0;
	if (fstat(fd, &buf) < 0)
	{
		if (fstat(STDIN_FILENO, &buf) < 0)
		{
	//		ft_putstr_fd("CLOSED: 0\n", 2);
			closefd[0] = 1;
		}
		if (fstat(STDOUT_FILENO, &buf) < 0)
		{
		//	ft_putstr_fd("CLOSED: 1\n", 2);
			closefd[1] = 1;
		}
		if (fstat(STDERR_FILENO, &buf) < 0)
		{
		//	ft_putstr_fd("CLOSED: 2\n", 2);
			closefd[2] = 1;
		}
		while (i < 3 && i <= fd)
		{
			if (closefd[i] == 1 && open(terminal, O_RDWR) < 0)
				ft_err_stderr(NULL, "open_fd_if_needed", "open failed");
				// error_exit("21sh: open_fd_if_needed: open failed\n"); //NO EXIT
			++i;
		}
		i = 0;
		while (i < 3 && i < fd)
		{
			if (closefd[i] == 1 && close(i) < 0)
				ft_err_stderr(NULL, "open_fd_if_needed", "close failed");
				// error_exit("21sh: open_fd_if_needed: close failed\n"); //NO EXIT
			++i;
		}
	}
}

void exec_redir(t_redir *node, char ***environ_cp, char *terminal, t_session *sesh)
{
	int fd;
//	int closeret;
	//fstat for future

	open_fd_if_needed(node->close_fd, terminal);
//	ft_printf("Redir close: %d and file: %s\n", node->close_fd, node->filepath);
//	closeret = close(node->close_fd);
	fd = open(node->filepath, node->open_flags, node->rights);
	if (fd < 0)
	{
		// exe_cmd_err("exec_redir", "open failed");
		ft_err_stderr(NULL, "exec_redir", "open failed");
		return ;
	}
//	close(node->close_fd);
	if (dup2(fd, node->close_fd) < 0)
	{
		// exe_cmd_err("exec_redir", "dup2 failed");
		ft_err_stderr(NULL, "exec_redir", "dup2 failed");
		return ;
	}
//	dup2(fd, node->close_fd);
	exec_tree(node->cmd, environ_cp, terminal, sesh);
//	reset_fd(terminal);
//	close(fd);
//	reset_fd(terminal);
}
