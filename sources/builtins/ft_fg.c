/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:46:44 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/10 13:05:00 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
	- How does the % work when used as parameter
		- % by itself || %% is same as %+ 
		- %number is the same as fg number
*/

int	ft_fg(char **cmd)
{
	int	nm;
	int	status;

	nm = ft_atoi(*(cmd + 1));
	waitpid(nm, &status, 0);
	return (0);
}

/*
	Args can be:
		- index
		- process name, but only if there is only one
*/

// int	ft_fg(t_proc *proc, char **cmd)
// {
// 	int		nm;
// 	int		status;
// 	t_proc	*ptr;

// 	ptr = proc;
// 	nm = ft_atoi(*(cmd + 1));
// 	waitpid(nm, &status, 0);
// 	return (0);
// }
