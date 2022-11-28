/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:13:43 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/26 19:57:09 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/**
 * It removes the environment variables specified by the user
 * 
 * @param sesh The session struct.
 * @param cmd The command line arguments.
 * 
 * @return The return value is the exit status of the last command executed.
 */
int	ft_unsetenv(t_session *sesh, char **cmd)
{
	int		i;
	char	*ptr;

	i = 0;
	while (*(cmd + (++i)))
	{
		if (ft_env_get(sesh, *(cmd + i)))
		{
			ptr = ft_strjoin(*(cmd + i), "=");
			ft_env_remove(sesh, ptr);
			ft_strdel(&ptr);
		}
	}
	return (0);
}
