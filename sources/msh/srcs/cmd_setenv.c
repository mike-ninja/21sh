/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_setenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:09:26 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/14 16:02:08 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	append_env(t_session *sesh, char **arg)
{
	char	**new_array;
	char	**ptr;
	int		i;

	i = array_len(sesh->env, END);
	new_array = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_array)
		ft_exit_no_mem(1);
	i = -1;
	ptr = sesh->env;
	while (ptr[++i])
		new_array[i] = ft_strdup(ptr[i]);
	new_array[i++] = ft_strdup(arg[0]);
	new_array[i] = NULL;
	env_clean(sesh->env);
	sesh->env = new_array;
	return (RESET);
}

bool	replace_value(t_session *sesh, char *arg, char **tmp)
{
	int		i;
	char	*key;
	char	*frag;

	i = -1;
	frag = NULL;
	key = ft_strsep(&arg, "=");
	while (sesh->env[++i])
	{
		frag = ft_strjoin(key, "=");
		if (!ft_strncmp(sesh->env[i], frag, ft_strlen(frag)))
		{
			if (tmp)
				*tmp = sesh->env[i];
			else
				ft_strdel(&sesh->env[i]);
			sesh->env[i] = ft_strjoin(frag, arg);
			ft_strdel(&frag);
			ft_strdel(&key);
			return (true);
		}
		ft_strdel(&frag);
	}
	ft_strdel(&key);
	return (false);
}

static void	invalid_env_msg(char **arg, int i)
{
	ft_printf("minishell: %s:", arg[0]);
	ft_printf(" `%s':", arg[i]);
	ft_printf(" not a valid identifier\n");
}

int	cmd_setenv(t_session *sesh)
{
	int	i;

	i = 1;
	while (sesh->tok->arg[i])
	{
		if (ft_strchr(sesh->tok->arg[i], '='))
		{
			if (*sesh->tok->arg[i] == '='
				|| (!ft_isalpha(*sesh->tok->arg[i])
					&& *sesh->tok->arg[i] != '_'))
			{
				invalid_env_msg(sesh->tok->arg, i);
			}
			else if (!replace_value(sesh,
					ft_strdup(sesh->tok->arg[i]), NULL))
				append_env(sesh, &sesh->tok->arg[i]);
		}
		i++;
	}
	return (RESET);
}
