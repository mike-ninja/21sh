/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:12:50 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/29 16:33:30 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

//TODO : Fix the leaks
// static void	update_cmd(t_session *sesh, char **cmd)
// {
// 	int		i;
// 	char	**new_cmd;

// 	new_cmd = (char **)ft_memalloc(sizeof(char *) * (ft_arrlen(cmd) + 1));
// 	i = -1;
// 	while (cmd[++i])
// 		(*new_cmd) + i = ft_strdup((*cmd) + i);
// 	(*new_cmd) + i = NULL;
// 	cmd = new_cmd;
// }

int	ft_env(t_session *sesh, char ***cmd)
{
	int	i;

	i = 1;
	if (*((*cmd) + i) && ft_strchr(*((*cmd) + i), '='))
		i = ft_env_temp(sesh, *cmd, i);
	// if (((*node->cmd) + i))
	// {
	// 	update_cmd(sesh, (*node->cmd) + i);
	// 	return (1); // Continue to run a command
	// }
	i = -1; 
	while (*(sesh->env + ++i))
		ft_putendl(*(sesh->env + i));
	return (0);
}
