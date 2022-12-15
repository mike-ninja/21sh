/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:14:38 by jakken            #+#    #+#             */
/*   Updated: 2022/12/15 16:58:52 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*	Open fd if it is closed. First opens all closed ones until
	fd, then opens fd, then closes all the rest which were closed */
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
