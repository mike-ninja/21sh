/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:55:11 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/11 12:52:19 by jniemine         ###   ########.fr       */
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
	char	*buff;

	i = -1;
	buff = NULL;
	while (cmd[++i])
	{
		expanded = NULL;
		if (*cmd[i] != '\'' && ft_strchr(cmd[i], '$') && ft_strlen(cmd[i]) > 1)
			expanded = ft_expansion_dollar(sesh, cmd[i]);
		else if (**(cmd + i) == '~')
			expanded = ft_expansion_tilde(sesh, cmd[i]);
		if (!expanded)
			buff = ft_strdup(cmd[i]);
		else
		{
			buff = ft_strdup(expanded);
			ft_strdel(&expanded);
		}
		ft_strdel(cmd + i);
		ft_quote_blash_removal(buff);
		cmd[i] = ft_strdup(buff);
		ft_strdel(&buff);
	}
}
