/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pid_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:04:08 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/17 10:50:30 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int pid_status(int pid) 
{
    int status;
	
    waitpid(pid, &status, WNOHANG | WUNTRACED);
	if (WIFEXITED(status))
		return 0; // Process has finished/
	else if (WIFSIGNALED(status))
	{
		if (WSTOPSIG(status))
			return 1; //  Process is suspended
		if (WTERMSIG(status))
			return 2; // Process terminated by a signal
	}
	return 3; // Process is running
}
