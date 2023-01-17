/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:55:11 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/17 11:05:37 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/**
 * It loops through each word in the command, and if it finds a dollar sign, 
 * it expands the variable.
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
