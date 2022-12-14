/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 13:50:01 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/14 19:45:40 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/**
 * It takes a session and a command, expands the command, and then checks if
 * the command is a builtin. If it is, it runs the builtin and returns the exit
 * status. If it's not, it returns 1.
 * 
 * @param sesh the session struct
 * @param cmd The command to be executed.
 * 
 * @return The return value of the builtin function.
 */
int	ft_builtins(t_session *sesh, char ***cmd)
{
	if (sesh && cmd)
	{
		ft_expansion(sesh, *cmd);
		if (!ft_strcmp(**cmd, "env"))
			return (ft_env(sesh, cmd));
		else if (!ft_strcmp(**cmd, "setenv"))
			return (ft_setenv(sesh, *cmd));
		else if (!ft_strcmp(**cmd, "unsetenv"))
			return (ft_unsetenv(sesh, *cmd));
		else if (!ft_strcmp(**cmd, "cd"))
			return (ft_cd(sesh, *cmd));
		else if (!ft_strcmp(**cmd, "echo"))
			return (ft_echo(*cmd));
		else if (!ft_strcmp(**cmd, "exit"))
			ft_exit(sesh, 0);
	}
	return (1);
}
