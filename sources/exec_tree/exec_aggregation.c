/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_aggregation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 20:26:00 by jakken            #+#    #+#             */
/*   Updated: 2022/12/12 13:01:01 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

//TODO DOES THIS WORK?
void exec_aggregate(t_aggregate *node, char ***environ_cp, char *terminal, t_session *sesh)
{
	int			dupret;
	struct stat	buf;
	char		*open_fd;
//	if (fork_wrap() == 0)
//	{
	//ft_printf("OPEN: %d and CLOSE: %d\n", node->open_fd, node->close_fd);
	//	dupret = dup2(node->close_fd, node->open_fd);
	//	ft_printf("DUPRET: %d\n", dupret);
	//open_fd_if_needed(node->close_fd, terminal);
	if (fstat(node->open_fd, &buf) < 0)
	{
		open_fd = ft_itoa(node->open_fd);
		exe_cmd_err("Bad file descriptor", open_fd);
		ft_strdel(&open_fd);
		return ;
	}
	if (dup2(node->close_fd, node->open_fd) < 0)
	{
		exe_cmd_err("failed", "dup2");
		return ;
	}
	exec_tree(node->cmd, environ_cp, terminal, sesh);
//		exit (0);
//	}
//	wait (0);
}
