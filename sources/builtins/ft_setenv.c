/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:13:13 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/11 19:53:27 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	key_check_fail_msg(char **cmd, int i)
{	
	ft_printf("{CYAN}21sh{RESET}: ");
	ft_printf("{BLUE}%s{RESET}: ", *cmd);
	ft_putstr(": `");
	ft_printf("{BLUE}%s{RESET}': ", *(cmd + i));
	ft_printf("{RED}not a valid identifier{RESET}\n");
}

static int	key_check(int ch)
{
	if (ch == '=' || (ft_isspecial(ch) && ch != '_') || ft_isdigit(ch))
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
