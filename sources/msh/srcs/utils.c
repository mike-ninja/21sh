/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:13:31 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/11 12:00:28 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_address(char *file)
{
	if (access(file, F_OK) != 0)
		return (INVALID);
	if (access(file, X_OK) != 0)
		return (NOACCESS);
	return (RESET);
}

char	**env_get_var(t_session *sesh, char *key)
{
	char	**env;

	env = sesh->env;
	while (*env)
	{
		if (ft_strnequ(*env, key, ft_strlen(key)))
			return (env);
		env++;
	}
	return (NULL);
}

int	array_len(char **array, bool pos)
{
	size_t	len;

	len = 0;
	while (*array)
	{
		if (!ft_strstr(*array, "OLDPWD="))
			len++;
		else if (pos)
			len++;
		array++;
	}
	return (len);
}

char	*skip_whitespace(char *str)
{
	if (str)
	{
		while (*str)
		{
			if (!ft_iswhitespace(*str))
				return (str);
			str++;
		}	
	}
	return (NULL);
}
