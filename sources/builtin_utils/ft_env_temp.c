/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_temp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 12:19:22 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/29 16:31:09 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	tmp_env_len(char **cmd)
{
	int	len;

	len = 0;
	while (*(cmd + len) && ft_strchr(*(cmd + len), '=') \
		&& *(*(cmd + len)) != '=')
		len++;
	return (len);
}

int	ft_env_temp(t_session *sesh, char **cmd, int i)
{
	int		j;
	char	*replaced;

	j = 0;
	replaced = NULL;
	sesh->tmp_env_key = (char **)ft_memalloc(sizeof(char *) * \
		(tmp_env_len(cmd + i) + 1));
	while (*(cmd + i) && ft_strchr(*(cmd + i), '=') && *(*(cmd + i)) != '=')
	{
		if (ft_env_replace(sesh, *(cmd + i), &replaced))
			*(sesh->tmp_env_key + j++) = replaced;
		else
		{
			ft_env_append(sesh, cmd + i);
			*(sesh->tmp_env_key + j++) = ft_strsub(*(cmd + i), 0, \
				ft_strchr(*(cmd + i), '=') - *(cmd + i));
		}
		i++;
	}
	*(sesh->tmp_env_key + j) = NULL;
	return (i);
}
