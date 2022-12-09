/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:55:11 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/09 15:24:51 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

// static int	ft_alphalen(char *str)
// {
// 	int	len;

// 	len = 0;
// 	if (str)
// 	{
// 		while (*str)
// 		{
// 			if (*str != '\"' && *str != '\'')
// 				len++;
// 			str++;
// 		}
// 	}
// 	return (len);
// }

// static int	ft_quote_remove(char **str)
// {
// 	int		i;
// 	int		j;
// 	int		valid;
// 	char	*new_arr;

// 	i = 0;
// 	j = -1;
// 	valid = 0;
// 	new_arr = NULL;
// 	if (*(*str) == '\"' || *(*str) == '\'')
// 	{
// 		if (*(*str) == '\'')
// 			valid = 1;
// 		new_arr = (char *)ft_memalloc(sizeof(char) * (ft_alphalen(*str) + 1));
// 		while ((*str)[++j])
// 		{
// 			if ((*str)[j] == '\"' || (*str)[j] == '\'')
// 				continue ;
// 			new_arr[i++] = (*str)[j];
// 		}
// 		new_arr[i] = '\0';
// 		ft_strdel(str);
// 		*str = new_arr;
// 	}
// 	return (valid);
// }

// static char	*ft_expansion_loop(t_session *sesh, char *buff, char **cmd, char **split)
// {
// 	int		i;
// 	char	*tofree;

// 	i = -1;
// 	ft_strdel(cmd);
// 	while (split[++i])
// 	{
// 		if (ft_strchr(split[i], '$') && ft_strlen(split[i]) > 1)
// 		{
// 			if (*split[i] != '\'')
// 			{
// 				tofree = split[i];
// 				split[i] = ft_expansion_dollar(sesh, split[i]);
// 				ft_strdel(&tofree);
// 			}
// 			ft_strcat(buff, split[i]);
// 		}
// 		else
// 			ft_strcat(buff, ft_expansion_tilde(sesh, split[i]));
// 		if (split[i + 1])
// 			ft_strcat(buff, " ");
// 		ft_strdel(&split[i]);
// 	}
// 	ft_memdel((void **)&split);
// 	return (buff);
// }
static void ft_expansion_loop(t_session *sesh, char *buff, char **cmd)
{
	int		i;
	char	*expanded;

	i = -1;
	expanded = NULL;
	if (ft_strchr(*cmd, '$') && ft_strlen(*cmd) > 1)
	{
		if (**cmd != '\'')
			expanded = ft_expansion_dollar(sesh, *cmd);
		if (expanded)
			ft_strcat(buff, expanded);
	}
	else
		ft_strcat(buff, ft_expansion_tilde(sesh, *cmd));
	ft_strdel(cmd);
}

// static char	*ft_quote_removal(char *buff)
// {
// 	int	i;
// 	int	j;

// 	j = 0;
// 	i = 0;
// 	while (buff[i])
// 	{
// 		if ((buff[i] == '\'' || buff[i] == '\"') && (!i || buff[i - 1] != '\\'))
// 			i++;
// 		buff[j++] = buff[i++];
// 	}
// 	return (ft_strdup(buff));
// }

void	ft_expansion(t_session *sesh, char **cmd)
{
	int		i;
	char	buff[BUFF_SIZE];

	i = -1;
	ft_bzero(buff, BUFF_SIZE);
	while (cmd[++i])
	{
		ft_expansion_loop(sesh, buff, &cmd[i]);
		cmd[i] = ft_strdup(buff);
		ft_strclr(buff);
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
