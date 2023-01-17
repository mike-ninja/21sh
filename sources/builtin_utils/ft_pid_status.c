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

int pid_status(pid_t pid) 
{
    int		status;
	pid_t	ret;

    ret = waitpid(pid, &status, WNOHANG);
	if (ret == -1 || ret == pid)
		return (0); // exited
	return (1); // Still active
}

// int pid_status(pid_t pid) 
// {
//     int		status;
// 	pid_t	ret;

//     ret = waitpid(pid, &status, WNOHANG);
// 	if (ret == -1 || ret == pid)
// 		return (0); // exited
// 	return (1); // Still active
// }
