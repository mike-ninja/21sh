/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 13:21:43 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/18 12:07:48 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

static char	**hard_set_env(char	**curr_env)
{
	int		i;
	char	**env;
	char	cwd[MAXPATHLEN];

	env = (char **)malloc(sizeof(char *) * (array_len(curr_env, START) + 4));
	if (!env)
		ft_exit_no_mem(1);
	i = 0;
	while (curr_env[i])
	{
		env[i] = ft_strdup(curr_env[i]);
		ft_strdel(&curr_env[i]);
		i++;
	}
	ft_memdel((void **)&curr_env);
	env[i++] = ft_strjoin("PWD=", getcwd(cwd, MAXPATHLEN));
	env[i++] = ft_strdup("SHLVL=1");
	env[i++] = ft_strdup("_=/usr/bin/env");
	env[i] = NULL;
	return (env);
}

char	**mandatory_env(t_session *sesh)
{
	if (!env_get_var(sesh, "PWD=") && !env_get_var(sesh, "SHLVL=")
		&& !env_get_var(sesh, "_="))
		sesh->env = hard_set_env(sesh->env);
	return (sesh->env);
}

char	**env_init(void)
{
	int		i;
	char	**env;

	env = (char **)malloc(sizeof(char *) * (array_len(environ, START) + 1));
	if (!env)
		ft_exit_no_mem(1);
	i = 0;
	while (*environ)
	{
		if (!ft_strstr(*environ, "OLDPWD="))
		{	
			if (ft_strstr(*environ, "SHLVL"))
				env[i] = shlvl(env[i], *environ);
			else
				env[i] = ft_strdup(*environ);
			i++;
		}
		environ++;
	}
	env[i] = NULL;
	return (env);
}
