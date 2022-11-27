/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:14:38 by jakken            #+#    #+#             */
/*   Updated: 2022/11/27 22:19:41 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void exec_redir(t_redir *node, char ***environ_cp)
{
	if (fork_wrap() == 0)
	{
		close (node->close_fd);
		if (open(node->filepath, node->open_flags, node->rights) < 0)
			error_exit("21sh: exec_redir: open failed\n");
		if (!node->cmd)
		{
			ft_printf("21sh: command not found\n");
			return ;
		}
		exec_tree(node->cmd, environ_cp);
	}
	wait (0);
}
