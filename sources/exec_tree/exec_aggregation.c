/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_aggregation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 20:26:00 by jakken            #+#    #+#             */
/*   Updated: 2022/12/15 16:06:06 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	exec_aggregate(t_aggregate *node, char ***environ_cp,
		char *terminal, t_session *sesh)
{
	int			dupret;
	struct stat	buf;
	char		*open_fd;

	open_fd_if_needed(node->close_fd, terminal);
	if (fstat(node->open_fd, &buf) < 0)
	{
		open_fd = ft_itoa(node->open_fd);
		ft_err_print(open_fd, NULL, "Bad file descriptor", 2);
		ft_strdel(&open_fd);
		return ;
	}
	if (dup2(node->open_fd, node->close_fd) < 0)
	{
		ft_err_print(NULL, "dup2", "failed", 2);
		return ;
	}
	exec_tree(node->cmd, environ_cp, terminal, sesh);
}
