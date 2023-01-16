/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:13:13 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/16 14:58:03 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	delete_var(t_session *sesh, int *i)
{
	ft_strdel(&sesh->intr_vars[*i]);
	sesh->intr_vars[*i] = sesh->intr_vars[*i + 1];
	while (sesh->intr_vars[*i + 1])
	{
		sesh->intr_vars[*i] = sesh->intr_vars[*i + 1];
		*i += 1;
	}
	sesh->intr_vars[*i] = NULL;
}

static int find_var_key(t_session *sesh, char *cmd, int var_len)
{
	int	i;
	int	k;
	int ret;

	i = 0;
	ret = 0;
	k = 0;
	while (sesh->intr_vars[i])
	{
		if (ft_strncmp(sesh->intr_vars[i], cmd, var_len) == 0
			&& sesh->intr_vars[i][var_len - 1] == '=')
		{
			ft_env_append(sesh, &sesh->intr_vars[i]);
			delete_var(sesh, &i);
			ret = 1;
			break;
		}
		i++;
	}
	return (ret);
}

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
int	ft_export(t_session *sesh, char **cmd)
{
	int		i;
	char	*key;

	i = 0;
	sesh->exit_stat = 0;
	key = NULL;
	while (*(cmd + ++i))
	{
		key = ft_strjoin(*(cmd + i) ,"=");
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
		else if (!find_var_key(sesh, key, ft_strlen(key)))
			;
		ft_strdel(&key);
	}
	return (0);
}
