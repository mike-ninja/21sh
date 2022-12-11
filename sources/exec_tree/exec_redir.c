/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:14:38 by jakken            #+#    #+#             */
/*   Updated: 2022/12/11 18:56:00 by jniemine         ###   ########.fr       */
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
		ft_putstr_fd("HELO\n", 2);
		if (fstat(STDIN_FILENO, &buf) < 0)
		{
			ft_putstr_fd("CLOSED: 0\n", 2);
			closefd[0] = 1;
		}
		if (fstat(STDOUT_FILENO, &buf) < 0)
		{
			ft_putstr_fd("CLOSED: 1\n", 2);
			closefd[1] = 1;
		}
		if (fstat(STDERR_FILENO, &buf) < 0)
		{
			ft_putstr_fd("CLOSED: 2\n", 2);
			closefd[2] = 1;
		}
	while (i < 3 && i <= fd)
	{
		if (closefd[i] == 1 && open(terminal, O_RDWR) < 0)
			error_exit("21sh: open_fd_if_needed: open failed\n");
		++i;
	}
	i = 0;
	while (i < 3 && i < fd)
	{
		if (closefd[i] == 1 && close(i) < 0)
			error_exit("21sh: open_fd_if_needed: close failed\n");
		++i;
	}
	}
}

//Should the error exit anymore? No fork
void exec_redir(t_redir *node, char ***environ_cp, char *terminal, t_session *sesh)
{
	int fd;
	int closeret;
	//fstat for future

	open_fd_if_needed(node->close_fd, terminal);
	closeret = close(node->close_fd);
	fd = open(node->filepath, node->open_flags, node->rights);
	if (fd < 0)
		error_exit("21sh: exec_redir: open failed\n");
//	dup2(fd, node->close_fd);
	exec_tree(node->cmd, environ_cp, terminal, sesh);
//	reset_fd(terminal);
//	close(fd);
//	reset_fd(terminal);
}
