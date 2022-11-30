/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:55:11 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/30 12:14:30 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	ft_alphalen(char *str)
{
	int	len;

	len = 0;
	if (str)
	{
		while (*str)
		{
			if (*str != '\"' && *str != '\'')
				len++;
			str++;
		}
	}
	return (len);
}

static int	ft_quote_remove(char **str)
{
	int		i;
	int		j;
	int		valid;
	char	*new_arr;

	i = 0;
	j = -1;
	valid = 0;
	new_arr = NULL;
	if (*(*str) == '\"' || *(*str) == '\'')
	{
		if (*(*str) == '\'')
			valid = 1;
		new_arr = (char *)ft_memalloc(sizeof(char) * (ft_alphalen(*str) + 1));
		while ((*str)[++j])
		{
			if ((*str)[j] == '\"' || (*str)[j] == '\'')
				continue ;
			new_arr[i++] = (*str)[j];
		}
		new_arr[i] = '\0';
		ft_strdel(str);
		*str = new_arr;
	}
	return (valid);
}

static char	*ft_expansion_loop(t_session *sesh, char *buff, char **tok_val, char **split)
{
	int		i;
	char	*tofree;

	i = -1;
	// ft_strdel(tok_val);
	while (split[++i])
	{
		if (ft_strchr(split[i], '$') && ft_strlen(split[i]) > 1)
		{
			if (!ft_quote_remove(&split[i]))
			{
				tofree = split[i];
				split[i] = ft_expansion_dollar(sesh, split[i]);
				ft_strdel(&tofree);
			}
			ft_strcat(buff, split[i]);
		}
		else
			ft_strcat(buff, ft_expansion_tilde(sesh, split[i]));
		if (split[i + 1])
			ft_strcat(buff, " ");
		ft_strdel(&split[i]);
	}
	ft_memdel((void **)&split);
	return (buff);
}

void	ft_expansion(t_session *sesh, char **cmd)
{
	int		i;
	char	buff[BUFF_SIZE];

	i = -1;
	while (cmd[++i])
	{
		ft_bzero(buff, BUFF_SIZE);
		cmd[i] = ft_strdup(ft_expansion_loop(sesh, buff, cmd + i, ft_strsplit(cmd[i], ' ')));
		// ft_putendl(cmd[i]);
	}
}

// void	ft_expansion(t_session *sesh)
// {
// 	int		i;
// 	char	buff[BUFF_SIZE];

// 	i = -1;
// 	while (sesh->tokens[++i].token)
// 	{
// 		ft_bzero(buff, BUFF_SIZE);
// 		sesh->tokens[i].value = ft_strdup(ft_expansion_loop(sesh, buff, \
// 			&sesh->tokens[i].value, ft_strsplit(sesh->tokens[i].value, ' ')));
// 	}
// }
