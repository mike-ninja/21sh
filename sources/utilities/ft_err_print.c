/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_err_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:04:08 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/13 21:26:40 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/**
 * It prints an error message
 * with the 21sh error message format
 * SHELL_NAME: cmd: file: msg
 * 
 * @param file The file that the error is coming from.
 * @param cmd The command that was run.
 * @param msg The error message to print.
 * 
 * @return 1
 */
// int ft_err_print(char *file, char *cmd, char *msg)
// {
// 	ft_printf("{CYAN}%s{RESET}: ", SHELL_NAME);
// 	if (cmd)
// 		ft_printf("{BLUE}%s{RESET}: ", cmd);
// 	if (file)
// 		ft_printf("%s: ", file);
// 	ft_printf("{RED}%s{RESET}\n", msg);
// 	return (1);
// }

int ft_err_print(char *file, char *cmd, char *msg, int fd)
{
    ft_putstr_fd(SHELL_NAME, fd);
    ft_putstr_fd(": ", fd);
	if (cmd)
	{
    	ft_putstr_fd(cmd, fd);
	    ft_putstr_fd(": ", fd);
	}
	if (file)
	{
		ft_putstr_fd(file, fd);
	    ft_putstr_fd(": ", fd);
	}
    ft_putstr_fd(msg, fd);
    ft_putstr_fd("\n", fd);
	return (1);
}
