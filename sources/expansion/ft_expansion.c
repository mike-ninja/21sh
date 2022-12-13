/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:55:11 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/13 12:50:20 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	ft_quote_removal(char *buff)
{
	int		i;
	int		k;

	k = 0;
	i = -1;
	while (buff[++i])
	{
		if (buff[i] != '\'' && buff[i] != '\"')
			buff[k++] = buff[i];
		else if (i && buff[i - 1] == '\\')
			buff[k++] = buff[i];
		else
			buff[k] = '\0';
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
	int		k;
	char	*expanded;
	char	buff[BUFF_SIZE];

	i = -1;
	ft_bzero(buff, BUFF_SIZE);
	while (cmd[++i])
	{
		if (*cmd[i] != '\'' && ft_strchr(cmd[i], '$') && ft_strlen(cmd[i]) > 1)
		{
			expanded = ft_expansion_dollar(sesh, cmd[i]);
			ft_strcat(buff, expanded);
			ft_strdel(&expanded);
		}
		else
			ft_strcat(buff, ft_expansion_tilde(sesh, cmd[i]));
		ft_quote_removal(buff);
		ft_strdel(cmd + i);
		cmd[i] = ft_strdup(buff);
		// ft_printf("{RED}cmd after expansion: %s{RESET}\n", cmd[i]);
		ft_strclr(buff);
	}
}
