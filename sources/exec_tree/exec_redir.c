/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:14:38 by jakken            #+#    #+#             */
/*   Updated: 2022/12/07 18:57:19 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void exec_redir(t_redir *node, char ***environ_cp, char *terminal)
{
	int fd;
	int closeret;

	closeret = close (node->close_fd);
	fd = open(node->filepath, node->open_flags, node->rights);
	if (fd < 0)
		error_exit("21sh: exec_redir: open failed\n");
	exec_tree(node->cmd, environ_cp, terminal);
	close(fd);
	reset_fd(terminal);
}
