/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 15:10:47 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/06 10:14:08 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*shlvl(char *my_env, char *env)
{
	char	*lvl;

	lvl = increment_lvl(env);
	my_env = ft_strjoin("SHLVL=", lvl);
	free(lvl);
	return (my_env);
}
