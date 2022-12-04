/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 20:31:23 by jniemine          #+#    #+#             */
/*   Updated: 2022/12/04 20:33:12 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_21sh.h"

/* Untested prototype */
// void	reset_filedescriptors(t_session *sesh)
// {
// 	char	*terminal;
// 	int		fd;

// 	terminal = sesh->terminal;
// 	while (fd >= 0)
// 	{
// 		fd = open(terminal, O_RDWR);
// 		if (fd >= 3)
// 		{
// 			close(fd);
// 			break ;
// 		}
// 	}
// }
void	reset_filedescriptors(t_session *sesh)
{
	char	*terminal;
	int		fd;

	terminal = sesh->terminal;
	close(0);
	fd = open(terminal, O_RDWR);
	close(1);
	fd = open(terminal, O_RDWR);
	close(2);
	fd = open(terminal, O_RDWR);
}

