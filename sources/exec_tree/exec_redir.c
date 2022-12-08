/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:14:38 by jakken            #+#    #+#             */
/*   Updated: 2022/12/08 16:58:19 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void exec_redir(t_redir *node, char ***environ_cp, char *terminal, t_session *sesh)
{
	int fd;
	//fstat for future

//	close(node->close_fd);
	fd = open(node->filepath, node->open_flags, node->rights);
	if (fd < 0)
		error_exit("21sh: exec_redir: open failed\n");
	dup2(fd, node->close_fd);
	exec_tree(node->cmd, environ_cp, terminal, sesh);
	close(fd);
//	reset_fd(terminal);
}
