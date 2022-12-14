/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 20:33:02 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/14 19:44:18 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/**
 * It checks if the file descriptor 1 (stdout) is valid
 * 
 * @return The return value of the function.
 */
static int	echo_fd_check(void)
{
	struct stat	buf;

	if (fstat(1, &buf) == -1)
	{
		ft_err_print(NULL, "echo", "write error: Bad file descriptor", 2);
		return (1);
	}
	return (0);
}

/**
 * It prints the arguments to the standard output, with a newline at the end,
 * unless the first argument is "-n", in which case it doesn't print the newline
 * 
 * @param cmd The command line arguments.
 * 
 * @return The return value of the function.
 */
int	ft_echo(char **cmd)
{
	bool	nl_flag;

	if (echo_fd_check())
		return (0);
	nl_flag = false;
	if (!(*cmd))
		ft_putstr("\n");
	else
	{
		if (!ft_strcmp(*(cmd++), "-n"))
			nl_flag = true;
		while (*cmd)
		{
			if (*cmd)
				ft_putstr(*cmd);
			cmd++;
			if (*cmd)
				ft_putstr(" ");
		}
		if (!nl_flag)
			ft_putstr("\n");
	}
	return (0);
}
