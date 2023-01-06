/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:13:13 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/06 13:00:31 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	key_check_fail_msg(char **cmd, int i)
{	
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(*cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("`", 2);
	ft_putstr_fd(*(cmd + i), 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

static int	key_check(int ch)
{
	if (ch == '=' || (ft_isspecial(ch) && ch != '_') || ft_isdigit(ch))
		return (0);
	else
		return (1);
}

/**
 * It checks for a valid key, then either replaces an existing key or appends 
 * a new key.
 * 
 * @param sesh the session struct
 * @param cmd The command line arguments
 * 
 * @return The return value is the exit status of the command.
 */
int	ft_setenv(t_session *sesh, char **cmd)
{
	int	i;

	i = 0;
	sesh->exit_stat = 0;
	while (*(cmd + ++i))
	{
		if (ft_strchr(*(cmd + i), '='))
		{
			if (!key_check(*(*(cmd + i))))
			{
				key_check_fail_msg(cmd, i);
				sesh->exit_stat = 1;
			}
			else if (!ft_env_replace(sesh, *(cmd + i), NULL))
				ft_env_append(sesh, cmd + i);
		}
	}
	return (0);
}
