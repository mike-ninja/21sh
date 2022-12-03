/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 20:31:23 by jniemine          #+#    #+#             */
/*   Updated: 2022/12/03 20:44:03 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_21sh.h"

/* Untested prototype */
void	reset_filedescriptors(t_session *sesh)
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
