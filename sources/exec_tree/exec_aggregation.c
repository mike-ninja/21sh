/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_aggregation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 20:26:00 by jakken            #+#    #+#             */
/*   Updated: 2022/11/30 21:03:53 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void exec_aggregate(t_aggregate *node, char ***environ_cp)
{
	if (fork_wrap() == 0)
	{
		if (dup2(node->open_fd, node->close_fd) < 0)
		{
			ft_printf("21sh: dup: bad filedescriptor\n");
			exit (0);
		}
		exec_tree(node->cmd, environ_cp);
		exit (0);
	}
	wait (0);
}
