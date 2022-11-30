/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 20:12:44 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/29 16:24:48 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	ft_env_append(t_session *sesh, char **arg)
{
	int		i;
	char	**new_array;

	i = -1;
	new_array = (char **)ft_memalloc(sizeof(char *) * (ft_arrlen(sesh->env) + 2));
	while (sesh->env[++i])
		new_array[i] = ft_strdup(sesh->env[i]);
	new_array[i++] = ft_strdup(*arg);
	new_array[i] = NULL;
	ft_arrclean(sesh->env);
	sesh->env = new_array;
	return (0);
}
// int	ft_env_append(t_session *sesh, char **arg)
// {
// 	char	**new_array;
// 	char	**ptr;
// 	int		i;

// 	i = ft_arrlen(sesh->env);
// 	new_array = (char **)malloc(sizeof(char *) * (i + 2));
// 	if (!new_array)
// 		ft_exit_no_mem(1);
// 	i = -1;
// 	ptr = sesh->env;
// 	while (ptr[++i])
// 		new_array[i] = ft_strdup(ptr[i]);
// 	new_array[i++] = ft_strdup(arg[0]);
// 	new_array[i] = NULL;
// 	ft_arrclean(sesh->env);
// 	sesh->env = new_array;
// 	return (0);
// }
