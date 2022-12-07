/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_closefd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 20:13:40 by jniemine          #+#    #+#             */
/*   Updated: 2022/12/07 18:20:40 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	exec_closefd(t_closefd *node, char ***environ_cp, char *terminal)
{
	int closeret;
	ft_putstr_fd("CLOSE: ", 2);
	ft_putstr_fd(ft_itoa(node->close_fd), 2);
	ft_putstr_fd("\n", 2);
	closeret = close(node->close_fd);
	ft_putstr_fd("CLOSERET: ", 2);
	ft_putstr_fd(ft_itoa(closeret), 2);
	ft_putstr_fd("\n", 2);
	if (node->cmd)
		exec_tree(node->cmd, environ_cp, terminal);
}
