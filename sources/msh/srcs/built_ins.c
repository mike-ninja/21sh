/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:47:54 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/20 09:09:10 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_echo(char **arg)
{
	bool	nl_flag;

	nl_flag = false;
	if (!*arg)
	{
		ft_putstr("\n");
		return (RESET);
	}
	if (!ft_strcmp(*arg, "-n"))
	{
		nl_flag = true;
		arg++;
	}
	while (*arg)
	{
		if (**arg)
			ft_printf("%s", *arg++);
		else
			arg++;
		if (*arg)
			ft_printf(" ");
	}
	if (!nl_flag)
		ft_printf("\n");
	return (RESET);
}

int	built_ins(t_session *sesh)
{
	if (ft_strcmp(*sesh->tok->arg, "env") == 0)
		return (cmd_env(sesh));
	if (ft_strcmp(*sesh->tok->arg, "setenv") == 0)
		return (cmd_setenv(sesh));
	if (ft_strcmp(*sesh->tok->arg, "unsetenv") == 0)
		return (cmd_unsetenv(sesh));
	if (ft_strcmp(*sesh->tok->arg, "echo") == 0)
		return (cmd_echo(sesh->tok->arg + 1));
	if (ft_strcmp(*sesh->tok->arg, "cd") == 0)
		return (cmd_cd(sesh));
	sesh->result = ERROR;
	return (sesh->result);
}
