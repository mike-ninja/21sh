/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:10:57 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/19 13:03:57 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_last_arg(char	**arg)
{
	if (!*arg)
		return (NULL);
	while (*arg)
		arg++;
	return (arg - 1);
}

static void	update_last_arg(t_session *sesh)
{
	char	*join;
	char	**env;
	char	**last_arg;

	join = NULL;
	env = env_get_var(sesh, "_=");
	last_arg = get_last_arg(sesh->tok->arg);
	if (last_arg)
	{
		if (env)
		{
			ft_strdel(env);
			*env = ft_strjoin("_=", *last_arg);
		}
		else
		{
			join = ft_strjoin("_=", *last_arg);
			append_env(sesh, &join);
			ft_strdel(&join);
		}
	}
}

static void	revert_existent_env(t_session *sesh, char **tm_en)
{
	int		i;
	char	c;
	char	**env;

	i = 0;
	while (tm_en[0][i] != '=')
		i++;
	c = tm_en[0][i + 1];
	tm_en[0][i + 1] = '\0';
	env = env_get_var(sesh, tm_en[0]);
	if (env)
	{
		ft_strdel(env);
		tm_en[0][i + 1] = c;
		*env = ft_strdup(tm_en[0]);
	}
}

static void	tmp_env(t_session *sesh)
{
	int		i;
	char	*key;

	i = -1;
	key = NULL;
	while (sesh->tm_en[++i])
	{
		if (ft_strchr(sesh->tm_en[i], '='))
		{
			revert_existent_env(sesh, &sesh->tm_en[i]);
		}
		else
		{
			key = ft_strjoin(sesh->tm_en[i], "=");
			env_removal(sesh, key);
			ft_strdel(&key);
		}
		ft_strdel(&sesh->tm_en[i]);
	}
	ft_memdel((void **)&sesh->tm_en);
}

void	cycle(t_session *sesh, bool pos)
{
	if (!pos)
		update_last_arg(sesh);
	else
	{
		if (sesh->tm_en)
			tmp_env(sesh);
		arg_clean(sesh->tok);
	}
}
