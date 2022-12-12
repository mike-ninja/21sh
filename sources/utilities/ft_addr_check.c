/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addr_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 18:27:40 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/12 17:50:54 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int addr_error(char *file, char *msg)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": cd: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

int	ft_addr_check(char *file)
{
	struct stat	buff;
	
	if (stat(file, &buff))
		addr_error(file, "No such file or directory");
	else
	{
		if (!S_ISDIR(buff.st_mode))
			addr_error(file, "Not a directory");
		else if (access(file, X_OK))
			addr_error(file, "Permission denied");
	}
	return (0);
}
