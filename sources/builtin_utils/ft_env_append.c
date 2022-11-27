/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 20:12:44 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/26 20:13:07 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	ft_env_append(t_session *sesh, char **arg)
{
	char	**new_array;
	char	**ptr;
	int		i;

	i = ft_arrlen(sesh->env, END);
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
