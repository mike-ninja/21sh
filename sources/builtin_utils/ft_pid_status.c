/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pid_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:04:08 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/16 12:05:16 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	pid_status(int pid)
{
	int		status;
	pid_t	return_pid;

	return_pid = waitpid(pid, &status, WNOHANG | WUNTRACED);
	// ft_printf("[%d]", status);
	if (WIFSTOPPED(status))
		ft_printf("stoppoed");
	if (return_pid == -1) 
		return (-1);
	else if (return_pid == 0) 
		return (1);
	else if (return_pid == pid) 
		return (0);
	return (-1);
}
