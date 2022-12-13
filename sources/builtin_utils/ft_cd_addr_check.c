/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_addr_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 18:27:40 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/13 21:57:08 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

// ./21

int	ft_cd_addr_check(char *file)
{
	struct stat	buff;
	
	if (stat(file, &buff))
		return(ft_error_print(file, "cd", "No such file or directory"));
	else
	{
		if (!S_ISDIR(buff.st_mode))
			return(ft_error_print(file, "cd", "Not a directory"));
		else if (access(file, X_OK))
			return(ft_error_print(file, "cd", "Permission denied"));
	}
	return (0);
}
