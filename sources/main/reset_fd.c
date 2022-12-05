/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 20:31:23 by jniemine          #+#    #+#             */
/*   Updated: 2022/12/05 16:19:46 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/* Untested prototype */
void	reset_fd(char *terminal)
{
	int		fd;

//	dup2(STDIN_FILENO, STDIN_FILENO);
//	dup2(STDOUT_FILENO, STDOUT_FILENO);
//	dup2(STDERR_FILENO, STDERR_FILENO);
	close (STDIN_FILENO);
	open(terminal, O_RDWR);
	close (STDOUT_FILENO);
	open(terminal, O_RDWR);
	close (STDERR_FILENO);
	open(terminal, O_RDWR);
//	while (fd >= 0)
//	{
//		fd = open(terminal, O_RDWR);
//		if (fd >= 3)
//		{
//			close(fd);
//			break ;
//		}
//	}
}
