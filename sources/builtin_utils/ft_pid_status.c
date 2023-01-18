/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pid_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:04:08 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/17 15:50:44y mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

// int pid_status(pid_t pid) 
// {
//     int		status;
// 	pid_t	ret;

//     ret = waitpid(pid, &status, WNOHANG);
// 	// if (WIFSIGNALED(status))
// 	// {
// 	// 	if (WTERMSIG(status) == SIGINT)
// 	// 		ft_putstr_fd("
// 	// }

// 	// if (ret == -1 || ret == pid)
// 	// 	return (0); // exited
// 	// return (1); // Still active
// }

// int pid_status(pid_t pid) 
// {
//     int		status;

//     waitpid(pid, &status, WNOHANG);
// 	if (WIFEXITED(status))
// 	{
// 		if (WEXITSTATUS(status) == 0)
// 			return (0);
// 		else
// 			return (1);
// 	}
// 	else if (WIFSIGNALED(status))
// 	{
// 		if (WSTOPSIG(status))§
// 		else if (WTERMSIG(status))
// 			return (2);
// 	}
// 	return (-1);
// }

int pid_status(int status) 
{
	if (WIFEXITED(status))
		return (0); // process finished
	else if (WIFSIGNALED(status))
	{
		if (WSTOPSIG(status))
			return (1); // process suspended
		else if (WTERMSIG(status))
			return (2); // process terminated
	}
	return (-1); // process still active?
}
