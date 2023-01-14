/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pid_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:04:08 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/14 22:41:38 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	pid_status(int pid)
{
	int		status;
	pid_t	return_pid;

	return_pid = waitpid(pid, &status, WNOHANG);
	if (return_pid == -1) 
		return (-1);
	else if (return_pid == 0) 
		return (1);
	else if (return_pid == pid) 
		return (0);
	return (-1);
}
