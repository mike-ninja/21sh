/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:14:38 by jakken            #+#    #+#             */
/*   Updated: 2022/12/03 20:11:05 by jniemine         ###   ########.fr       */
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
		exec_tree(node->cmd, environ_cp);
		exit (0);
	}
	wait (0);
}
