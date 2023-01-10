/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:33:14 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/10 16:52:57 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	hash_error_print(char *arg)
{
	ft_putstr_fd("21sh: hash: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": not found\n", 2);
	return (-1);
}

static void	hash_clear(t_hash **ht)
{
	t_hash	*tmp;
	t_hash	*tmp2;
	int		i;

	i = -1;
	while (++i < HASH_SIZE)
	{
		if (ht[i])
		{
			tmp = ht[i];
			while (tmp)
			{
				tmp2 = tmp->next;
				free(tmp->program);
				// free(tmp);
				tmp = tmp2;
			}
			ht[i] = NULL;
		}
	}
}

void	hash_set(t_session *sesh, char **arg)
{
	int		i;
	int		index;
	char	*exepath;
	t_hash	*tmp;

	i = -1;
	while (arg[++i])
	{
		if (!ft_strnequ(arg[i], "hash", 4) && (exepath = search_bin(arg[i], sesh->env)))
		{
			index = hash_function(arg[i]);
			tmp = sesh->ht[index];
			while (tmp && !ft_strequ(exepath, tmp->program))
				tmp = tmp->next;
			if (tmp == NULL)
				hash_init_struct(sesh, exepath);
			ft_strdel(&exepath);
		}
		else if (!ft_strnequ(arg[i], "hash", 4))
		{
			hash_error_print(arg[i]);
			return ;
		}
	}
}

int	ft_hash(t_session *sesh, char **arg)
{

	if (ft_strnequ(arg[0], "hash", 4) && !arg[1])
		hash_print(sesh->ht);
	else if (ft_strnequ(arg[0], "hash", 4) && ft_strnequ(arg[1], "-r", 2))
		hash_clear(sesh->ht);
	hash_set(sesh, arg);
	return (1);
}
