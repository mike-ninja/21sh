/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 13:50:01 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/06 20:47:20 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	ft_builtins(t_session *sesh)
{
	char **cmd;

	if (sesh->head && ((t_semicolon *)sesh->head)->left->type == CMD)
	{
		cmd = ((t_cmdnode *)((t_semicolon *)sesh->head)->left)->cmd;
		ft_expansion(sesh, cmd);
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
		else if (!ft_strcmp(*cmd, "exit"))
			ft_exit(sesh, 0);
	}
	return (1);
}
