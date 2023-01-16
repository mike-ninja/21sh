/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pid_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:04:08 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/16 20:49:21 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

// int	pid_status(int pid)
// {
// 	int		status;
// 	pid_t	return_pid;

// 	return_pid = waitpid(pid, &status, WNOHANG);
// 	// ft_printf("[%d]", status);
// 	if (WIFSTOPPED(status))
// 		ft_printf("stoppoed");
// 	if (return_pid == -1) 
// 		return (-1);
// 	else if (return_pid == 0) 
// 		return (1);
// 	else if (return_pid == pid) 
// 		return (0);
// 	return (-1);
// }

// #include <sys/wait.h>

int pid_status(int pid) 
{
    int status;
	
	ft_printf("%d", pid);
    waitpid(pid, &status, WUNTRACED | WNOHANG);
    // if (WIFSTOPPED(status))
    //     return 1; // Process suspended
    // if (WIFEXITED(status))
    //     return 0; // Process finished
    // else if (WTERMSIG(status))
    //     
    // else
    //     return 3; // Process is still running
	ft_printf("status %d\n", status);
	if (WIFEXITED(status))
		return 0; // Process has finished/
	else if (WIFSIGNALED(status))
	{
		if (WIFSTOPPED(status))
			return 1; //  Process is suspended
		if (WTERMSIG(status))
			return 2; // Process terminated by a signal
	}
	return 3; // Process is running
}
