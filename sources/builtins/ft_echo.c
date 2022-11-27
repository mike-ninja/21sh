/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 20:33:02 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/27 13:38:12 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

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

	nl_flag = false;
	if (!(*cmd))
		ft_putstr("\n");
	else
	{
		if (!ft_strcmp(*(cmd++), "-n"))
			nl_flag = true;
		while (*cmd)
		{
			if (*(*(cmd++)))
				ft_putstr(*cmd);
			if (*cmd)
				ft_putstr(" ");
		}
		if (!nl_flag)
			ft_putstr("\n");
	}
	return (0);
}