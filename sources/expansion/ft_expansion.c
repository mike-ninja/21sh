/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:55:11 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/13 22:32:57 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

// static void	ft_quote_blash_removal(char *buff)
// {
// 	int		i;
// 	int		k;

// 	k = 0;
// 	i = -1;
// 	while (buff[++i])
// 	{
// 		if (buff[i] != '\'' && buff[i] != '\"')
// 			buff[k++] = buff[i];
// 		else if (i && buff[i - 1] == '\\')
// 			buff[k++] = buff[i];
// 		else
// 			buff[k] = '\0';
// 	}
// }
static void	ft_quote_blash_removal(char *buff)
{
	int		i;
	int		k;

	k = 0;
	i = -1;
	while (buff[++i])
	{
		if (buff[i] == '\\')
		{
			i++;
			if (buff[i] == '\'' || buff[i] == '\"' || buff[i] == '\n')
				i++;
		}
		else if ((buff[i] == '\'' || buff[i] == '\"'))
			i++;
		buff[k++] = buff[i];
	}
}

/**
 * It loops through each word in the command, and if it finds a dollar sign, it expands the variable
 * 
 * @param sesh the session struct
 * @param cmd the command to be expanded
 */
void	ft_expansion(t_session *sesh, char **cmd)
{
	int		i;
	char	*expanded;
	char	buff[BUFF_SIZE];

	i = -1;
	ft_bzero(buff, BUFF_SIZE);
	while (cmd[++i])
	{
		expanded = NULL;
		if (*cmd[i] != '\'' && ft_strchr(cmd[i], '$') && ft_strlen(cmd[i]) > 1)
			expanded = ft_expansion_dollar(sesh, cmd[i]);
		else if (**(cmd + i) == '~')
			expanded = ft_expansion_tilde(sesh, cmd[i]);
		if (!expanded)
			ft_strcat(buff, cmd[i]);
		else
		{
			ft_strcat(buff, expanded);
			ft_strdel(&expanded);
		}
		ft_strdel(cmd + i);
		ft_quote_blash_removal(buff);
		cmd[i] = ft_strdup(buff);
		ft_strclr(buff);
	}
}
