/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:16:26 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/18 21:05:34 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_failed_arg(char *str)
{
	while (*str)
	{
		if (*str == '\n')
		{
			write(1, "\\", 1);
			write(1, "n", 1);
		}
		else
			write(1, str, 1);
		str++;
	}
}

static void	error_message_cont(t_session *sesh)
{
	if (sesh->result == NOCOMMAND)
		ft_printf("command not found\n");
	if (sesh->result == TOOMANYARGS)
		ft_printf("too many arguments\n");
	if (sesh->result == NONEXE)
	{
		if (sesh->tok->arg[1])
			print_failed_arg(sesh->tok->arg[1]);
		ft_printf("not an executable\n");
	}
	sesh->result = ERROR;
}

void	error_message(t_session *sesh)
{
	ft_printf("minishell: ");
	print_failed_arg(sesh->tok->arg[0]);
	write(1, ": ", 2);
	if (sesh->result == INVALID)
	{
		if (!ft_strcmp(sesh->tok->arg[0], "cd"))
		{
			print_failed_arg(sesh->tok->arg[1]);
			write(1, ": ", 2);
		}
		ft_printf("No such file or directory\n");
	}
	if (sesh->result == NOACCESS)
	{
		if (sesh->tok->arg[1])
			print_failed_arg(sesh->tok->arg[1]);
		ft_printf("Permission denied\n");
	}
	error_message_cont(sesh);
}
