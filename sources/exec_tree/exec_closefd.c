/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_closefd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 20:13:40 by jniemine          #+#    #+#             */
/*   Updated: 2022/12/08 17:00:04 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	exec_closefd(t_closefd *node, char ***environ_cp, char *terminal, t_session *sesh)
{
	close(node->close_fd);
	if (node->cmd)
		exec_tree(node->cmd, environ_cp, terminal, sesh);
//	reset_fd(terminal);
}
