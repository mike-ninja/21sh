/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:14:38 by jakken            #+#    #+#             */
/*   Updated: 2022/12/14 21:35:11 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/* Expand for range from 0 to fd */
void	open_fd_if_needed(int fd, char *terminal)
{
	struct stat	buf;
	int			closefd[3];
	int			i;

	ft_bzero((void *)closefd, sizeof(closefd));
	i = 0;
	if (fstat(fd, &buf) < 0)
	{
		if (fstat(STDIN_FILENO, &buf) < 0)
			closefd[0] = 1;
		if (fstat(STDOUT_FILENO, &buf) < 0)
			closefd[1] = 1;
		if (fstat(STDERR_FILENO, &buf) < 0)
			closefd[2] = 1;
		while (i < 3 && i <= fd)
		{
			if (closefd[i] == 1 && open(terminal, O_RDWR) < 0)
				ft_err_print(NULL, "open_fd_if_needed", "open failed", 2);
			++i;
		}
		i = 0;
		while (i < 3 && i < fd)
		{
			if (closefd[i] == 1 && close(i) < 0)
				ft_err_print(NULL, "open_fd_if_needed", "close failed", 2);
			++i;
		}
	}
}

void	exec_redir(t_redir *node, char ***environ_cp,
				char *terminal, t_session *sesh)
{
	int	fd;

	open_fd_if_needed(node->close_fd, terminal);
	fd = open(node->filepath, node->open_flags, node->rights);
	if (fd < 0)
	{
		ft_err_print(NULL, "exec_redir", "open failed", 2);
		return ;
	}
	if (dup2(fd, node->close_fd) < 0)
	{
		ft_err_print(NULL, "exec_redir", "dup2 failed", 2);
		return ;
	}
	exec_tree(node->cmd, environ_cp, terminal, sesh);
}
