/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_closefd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 20:31:23 by jniemine          #+#    #+#             */
/*   Updated: 2022/12/05 16:36:35 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	exec_closefd(t_closefd *node, char ***environ_cp)
{
	char	*terminal;
	int		fd;

	terminal = sesh->terminal;
	while (fd >= 0)
	{
		fd = open(terminal, O_RDWR);
		if (fd >= 3)
		{
			close(fd);
			break ;
		}
	}
}

