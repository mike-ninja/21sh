/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion_tilde.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:57:35 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/23 15:13:21 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/**
 * It returns the environment variable name that corresponds to the tilde key
 * 
 * @param str The string to be expanded.
 * 
 * @return The key for the environment variable.
 */
static char	*tilde_key(char *str)
{
	if (!ft_strcmp(str, "~+"))
		return ("PWD");
	else if (!ft_strcmp(str, "~-"))
		return ("OLDPWD");
	else if (!ft_strcmp(str, "~"))
		return ("HOME");
	return (NULL);
}

/**
 * It takes a string and returns a string with the tilde expanded.
 * 
 * @param sesh the session struct
 * @param str the string to be expanded
 * 
 * @return The value of the key in the environment.
 */
char	*ft_expansion_tilde(t_session *sesh, char *str)
{
	char	**env;
	char	*key;

	env = NULL;
	key = tilde_key(str);
	if (key)
	{
		env = ft_env_get(sesh, key);
		if (env)
			return (ft_strchr(*env, '=') + 1);
	}
	return (str);
}
