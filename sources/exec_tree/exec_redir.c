/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:14:38 by jakken            #+#    #+#             */
/*   Updated: 2022/12/15 14:49:14 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*	Open fd if it is closed. First opens all closed ones until
	fd, then opens fd, then closes all the rest which were closed */
void	open_fd_if_needed(int fd, char *terminal)
{
	struct stat	buf;
	int			*closefd;
	int			i;


	closefd = ft_memalloc(fd + 1);
	i = 0;
	if (fstat(fd, &buf) < 0)
	{
		while (i <= fd)
		{
			if (fstat(i, &buf) < 0)
				closefd[i] = 1;
			++i;
		}
		i = -1;
		while (1)
		{
			i = open(terminal, O_RDWR);
			if (i < 0)
				ft_err_print(NULL, "open_fd_if_needed", "open failed", 2);
			if (i >= fd)
				break ;
		}
		i = 0;
		while (i < fd)
		{
			if (closefd[i] == 1 && close(i) < 0)
				ft_err_print(NULL, "open_fd_if_needed", "close failed", 2);
			++i;
		}
	}
	free(closefd);
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
