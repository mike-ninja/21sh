/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:12:50 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/02 20:30:19 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	ft_env(t_session *sesh, char ***cmd)
{
	int	i;

	i = 1;
	if (*((*cmd) + i) && ft_strchr(*((*cmd) + i), '='))
		i = ft_env_temp(sesh, *cmd, i);
	i = -1; 
	while (*(sesh->env + ++i))
		ft_putendl(*(sesh->env + i));
	return (0);
}
