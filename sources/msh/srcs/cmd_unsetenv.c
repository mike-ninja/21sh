/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unsetenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:11:06 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/14 16:02:29 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_removal(t_session *sesh, char *env)
{
	char	**new_array;
	char	**ptr;
	int		i;

	new_array = (char **)malloc(sizeof(char *) * array_len(sesh->env, END));
	if (!new_array)
		ft_exit_no_mem(1);
	i = 0;
	ptr = sesh->env;
	while (*ptr)
	{
		if (!ft_strnequ(*ptr, env, ft_strlen(env)))
			new_array[i++] = ft_strdup(*ptr);
		ptr++;
	}
	new_array[i] = NULL;
	env_clean(sesh->env);
	sesh->env = new_array;
	return (1);
}

int	cmd_unsetenv(t_session *sesh)
{
	int		i;
	char	*ptr;

	i = 1;
	ptr = NULL;
	while (sesh->tok->arg[i])
	{
		ptr = ft_strjoin(sesh->tok->arg[i], "=");
		if (ptr)
		{
			if (env_get_var(sesh, ptr))
				if (env_removal(sesh, ptr) == 0)
					return (ERROR);
			ft_strdel(&ptr);
		}
		i++;
	}
	return (RESET);
}
