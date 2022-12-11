/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addr_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 18:27:40 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/11 19:30:44 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int addr_error(char *file, int err)
{
	if (err == -1)
		ft_printf("{CYAN}21sh{RESET}: {BLUE}cd{RESET}: %s: {RED}No such file or directory{RESET}\n", file);
	if (err == -2)
		ft_printf("{CYAN}21sh{RESET}: {BLUE}cd{RESET}: %s: {RED}Not a directory{RESET}\n", file);
	if (err == -3)
		ft_printf("{CYAN}21sh{RESET}: {BLUE}cd{RESET}: %s: {RED}Permission denied{RESET}\n", file);
	return (1);
}

// int	ft_addr_check(char *file)
// {
// 	struct stat		buf;
	
	
// 	if (access(file, F_OK) != 0)
// 	{
// 		addr_error(file, -1);
// 		return (-1);
// 	}
// 	if (access(file, X_OK) != 0)
// 		return (-2);
// 	return (0);
// }
// int	ft_addr_check(char *file)
// {
// 	struct stat	buff;
	
// 	if (access(file, F_OK))
// 		return (addr_error(file, -1));
// 	else if (!stat(file, &buff) && buff.st_mode != S_IFDIR)
// 		return (addr_error(file, -2));
// 	else if (access(file, X_OK))
// 		return (addr_error(file, -3));
// 	return (0);
// }
int	ft_addr_check(char *file)
{
	struct stat	buff;
	
	if (stat(file, &buff))
		addr_error(file, -1);
	else
	{
		if (!S_ISDIR(buff.st_mode))
			addr_error(file, -2);
		else if (access(file, X_OK))
			addr_error(file, -3);
	}
	return (0);
}
