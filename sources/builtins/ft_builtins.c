/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 13:50:01 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/30 11:00:12 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	ft_builtins(t_session *sesh)
{
	char **cmd;

	cmd = ((t_cmdnode *)sesh->head)->cmd;
	if (sesh->head && sesh->head->type == CMD)
	{
		if (!ft_strcmp(*cmd, "env"))
			return (ft_env(sesh, &cmd));
		else if (!ft_strcmp(*cmd, "setenv"))
			return (ft_setenv(sesh, cmd));
		else if (!ft_strcmp(*cmd, "unsetenv"))
			return (ft_unsetenv(sesh, cmd));
		else if (!ft_strcmp(*cmd, "cd"))
			return (ft_cd(sesh, cmd));
		else if (!ft_strcmp(*cmd, "echo"))
			return (ft_echo(cmd));
	}
	return (1);
}
