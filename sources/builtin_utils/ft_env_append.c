/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 20:12:44 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/16 14:00:47 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	ft_env_append(t_session *sesh, char **arg)
{
	int		i;
	char	**new_array;

	i = -1;
	new_array = (char **)ft_memalloc(sizeof(char *) * \
	(ft_arrlen(sesh->env) + 2));
	while (sesh->env[++i])
		new_array[i] = ft_strdup(sesh->env[i]);
	new_array[i++] = ft_strdup(*arg);
	new_array[i] = NULL;
	ft_arrclean(sesh->env);
	sesh->env = new_array;
	return (0);
}
