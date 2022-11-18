/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 11:44:19 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/20 12:15:00 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_prefix(char **arg, t_dollar *attr)
{
	int		len;
	char	*ret;
	int		dollar;

	len = 0;
	ret = NULL;
	dollar = 0;
	if (arg[0][len] && arg[0][len] == '$')
		dollar = 1;
	while (arg[0][len] && arg[0][len] != '$')
		len++;
	if (arg[0][len] && len)
	{
		ret = (char *)ft_memalloc(sizeof(char) * (len + 1));
		ft_bzero((char *)ret, len + 1);
		len = -1;
		while (arg[0][++len] && arg[0][len] != '$')
			ret[len] = arg[0][len];
		ft_strdel(arg);
		*arg = ret;
	}
	else if (dollar && !attr->i)
		ft_strdel(arg);
}

static void	dollar_swap_util(char **arg, char **env, t_dollar *attr)
{
	char	*extra;

	get_prefix(arg, attr);
	extra = get_extra(&attr->keys[attr->i]);
	find_match_env(arg, env, attr);
	if (extra)
	{
		if (!*arg)
			*arg = extra;
		else
		{
			*arg = strjoin_head(*arg, extra);
			ft_strdel(&extra);
		}
	}
}

static void	dollar_struct(t_dollar *attr)
{
	attr->i = -1;
	attr->keys = NULL;
	attr->match = false;
}

static char	*dollar_swap(char **arg, char **env)
{
	char		*hay;
	t_dollar	attr[1];

	dollar_struct(attr);
	hay = ft_strchr(*arg, '$');
	if (hay)
		hay = ft_strdup(hay);
	attr->keys = ft_strsplit(*arg, '$');
	while (attr->keys[++attr->i])
	{
		if (hay && ft_strstr(hay, attr->keys[attr->i]))
			dollar_swap_util(arg, env, attr);
		ft_strdel(&attr->keys[attr->i]);
	}
	ft_strdel(&hay);
	ft_memdel((void **)&attr->keys);
	return (*arg);
}

void	dollar_parse(t_session *sesh)
{
	int	i;

	i = -1;
	while (sesh->tok->arg[++i])
	{
		if (!ft_strcmp(sesh->tok->arg[i], "$$"))
		{
			ft_strdel(&sesh->tok->arg[i]);
			sesh->tok->arg[i] = ft_itoa(getpid());
		}
		else if (sesh->tok->tok[i] && (ft_strlen(sesh->tok->arg[i]) > 1))
		{
			sesh->tok->arg[i] = dollar_swap(
					&sesh->tok->arg[i], sesh->env);
		}
		if (!sesh->tok->arg[i])
			sesh->tok->arg[i] = ft_strdup("");
	}
}
