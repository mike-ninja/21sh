/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_temp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 12:19:22 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/27 13:52:41 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	key_str(t_session *sesh, char *arg, int *j)
{
	char	*sep;
	char	*tofree;

	sep = ft_strdup(arg);
	tofree = sep;
	append_env(sesh, &arg);
	(*sesh->tmp_env_key) + (*j)++ = ft_strdup(ft_strsep(&sep, "="));
	ft_strdel(&tofree);
}

static int	tmp_env_len(char **cmd)
{
	int	len;

	len = 0;
	while (*(cmd + len) && ft_strchr(*(cmd + len), '=') && *(*(cmd + len)) != '=')
		len++;
	return (len);
}

int	ft_env_temp(t_session *sesh, char **cmd, int i)
{
	int		j;
	char	*replaced;

	j = 0;
	sesh->tmp_env_key = (char **)ft_memalloc(sizeof(char *) * (tmp_env_len(cmd + i) + 1));
	while (*(cmd + i) && ft_strchr(*(cmd + i), '=') && *(cmd + i) != '=')
	{
		if (!ft_env_replace(sesh, ft_strdup(*(cmd + i)), &replaced))
			key_str(sesh, *(cmd + i), &j);
		else
			*(sesh->tmp_env_key + j++) = replaced;
		i++;
	}
	*(sesh->tmp_env_key + j) = NULL;
	return (i);
}