/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:42:26 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/22 19:53:58 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

extern char	**environ;

/**
 * It increments the level number in the environment variable.
 * 
 * @param env the environment variable that we want to change
 * 
 * @return The return value is the number of bytes that were written to the
 * file.
 */
static char	*increment_lvl(char *env)
{
	int		i;
	int		lvl;

	i = 0;
	while (env[i] < '0' || env[i] > '9')
		i++;
	lvl = ft_atoi(&env[i]);
	if (lvl < 1000)
		lvl++;
	else
		lvl = 0;
	return (ft_itoa(lvl));
}

/**
 * It takes the environment variable SHLVL, increments it by one.
 * 
 * @param my_env the environment variable that will be added to the environment
 * @param env the environment variable that we're looking for
 * 
 * @return a string that is the SHLVL environment variable.
 */
static char	*ft_shlvl(char *my_env, char *env)
{
	char	*lvl;

	lvl = increment_lvl(env);
	my_env = ft_strjoin("SHLVL=", lvl);
	free(lvl);
	return (my_env);
}

/**
 * It initializes the environment array.
 * 
 * @return A pointer to a pointer to a char.
 */
char	**ft_env_init(void)
{
	int		i;
	char	**env;

	env = (char **)malloc(sizeof(char *) * (ft_arrlen(environ) + 1));
	if (!env)
		ft_exit_no_mem(1);
	i = -1;
	while (environ[++i])
	{
		if (ft_strstr(environ[i], "SHLVL="))
			env[i] = ft_shlvl(env[i], environ[i]);
		else
			env[i] = ft_strdup(environ[i]);
	}
	env[i] = NULL;
	return (env);
}
