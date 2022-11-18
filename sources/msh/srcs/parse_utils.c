/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:15:37 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/20 12:10:36 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prefix(char **arg, char *str)
{
	if (!*arg)
		*arg = ft_strdup(str);
	else
		*arg = strjoin_head(*arg, str);
	return (*arg);
}

char	*get_extra(char **keys)
{
	int		i;
	char	*ptr;

	i = 0;
	while (keys[0][i] && (ft_isalpha(keys[0][i])
		|| ft_isalnum(keys[0][i]) || keys[0][i] == '_'))
		i++;
	if (keys[0][i])
	{
		ptr = ft_strdup(&keys[0][i]);
		return (ptr);
	}
	else
		return (NULL);
}

static int	break_string(int i, char *str)
{
	if (!i)
	{
		while (str[i] != '=')
			i++;
		str[i] = '\0';
	}
	else
		str[i] = '=';
	return (i);
}

static void	fix_string(int i, char *str)
{
	break_string(i, str);
}

void	find_match_env(char **arg, char **env, t_dollar *attr)
{
	int		i;

	while (env[0])
	{
		i = break_string(0, env[0]);
		if (ft_strncmp(env[0], attr->keys[attr->i],
				ft_strlen(env[0])) == 0)
		{
			*arg = prefix(arg, &env[0][i + 1]);
			fix_string(i, env[0]);
			attr->match = true;
			return ;
		}
		fix_string(i, env[0]);
		env++;
	}
}
