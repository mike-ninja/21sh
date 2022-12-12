/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_aggregation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 20:26:00 by jakken            #+#    #+#             */
/*   Updated: 2022/12/12 10:26:52 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

//TODO DOES THIS WORK?
void exec_aggregate(t_aggregate *node, char ***environ_cp, char *terminal, t_session *sesh)
{
//	if (fork_wrap() == 0)
//	{
	ft_printf("OPEN: %d and CLOSE: %d\n", node->open_fd, node->close_fd);
		if (dup2(node->close_fd, node->open_fd) < 0)
		{
			ft_printf("21sh: dup: bad filedescriptor\n");
			exit (0);
		}
		exec_tree(node->cmd, environ_cp, terminal, sesh);
//		exit (0);
//	}
//	wait (0);
}
