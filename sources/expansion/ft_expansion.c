/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:55:11 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/23 15:12:28 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/**
 * It splits the token value on spaces, and then for each word, it checks if
 * it contains a dollar sign. If it does, it calls ft_expansion_dollar, which
 * will expand the word. If it doesn't, it calls ft_expansion_tilde, which will
 * expand the word.
 * 
 * @param sesh the session struct
 * @param buff the buffer that will be returned
 * @param token_value the value of the token, which is the string to be expanded
 * 
 * @return A string
 */
static char	*ft_expansion_loop(t_session *sesh, char *buff, char **token_value)
{
	int		i;
	char	*tofree;
	char	**split;

	i = -1;
	tofree = NULL;
	split = ft_strsplit(*token_value, ' ');
	ft_strdel(token_value);
	while (split[++i])
	{
		if (ft_strchr(split[i], '$') && ft_strlen(split[i]) > 1)
		{
			tofree = ft_expansion_dollar(sesh, split[i]);
			ft_strcat(buff, tofree);
			ft_strdel(&tofree);
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

/**
 * This function expands the tokens.
 * 
 * @param sesh The session struct.
 * 
 * @return The expanded tokens.
 */
void	ft_expansion(t_session *sesh)
{
	int		i;
	char	buff[BUFF_SIZE];

	i = -1;
	while (sesh->tokens[++i].token)
	{
		ft_bzero(buff, BUFF_SIZE);
		sesh->tokens[i].value = ft_strdup(ft_expansion_loop(sesh, buff, \
			&sesh->tokens[i].value));
	}
}
