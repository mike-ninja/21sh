/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:12:50 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/12 20:38:51 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int update_cmd(t_session *sesh, char ***cmd, int i)
{
	int		k;
	int		len;
	char	**new;

	k = 0;
	len = ft_arrlen(*cmd + i);
	new = (char **)ft_memalloc(sizeof(char *) * (len + 1));
	while (*((*cmd) + i))
		*(new + k++) = ft_strdup(*((*cmd) + i++));
	*(new + k) = NULL;
	ft_arrclean(*cmd);
	*cmd = new;
	((t_cmdnode *)sesh->head)->cmd = *cmd;
	return (1);
}

int	ft_env(t_session *sesh, char ***cmd)
{
	int	i;

	i = 1;
	if (*((*cmd) + i) && ft_strchr(*((*cmd) + i), '='))
		i = ft_env_temp(sesh, *cmd, i);
	if (*((*cmd) + i))
		return (update_cmd(sesh, cmd, i));
	i = -1; 
	while (*(sesh->env + ++i))
		ft_putendl(*(sesh->env + i));
	return (0);
}
