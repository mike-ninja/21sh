/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:13:13 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/30 10:08:23 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	key_check_fail_msg(char **cmd, int i)
{
	ft_putstr("21sh: ");
	ft_putstr(*cmd);
	ft_putstr(": `");
	ft_putstr(*(cmd + i));
	ft_putendl("': not a valid identifier");
}

static int	key_check(int ch)
{
	if (ch == '=' || (ft_isspecial(ch) && ch != '_'))
		return (0);
	else
		return (1);
}

int	ft_setenv(t_session *sesh, char **cmd)
{
	int	i;

	i = 0;
	while (*(cmd + ++i))
	{
		if (ft_strchr(*(cmd + i), '='))
		{
			if (!key_check(*(*(cmd + i))))
				key_check_fail_msg(cmd, i);
			else if (!ft_env_replace(sesh, *(cmd + i), NULL))
				ft_env_append(sesh, cmd + i);
		}
	}
	return (0);
}
