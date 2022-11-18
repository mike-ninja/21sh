/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:05:26 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/18 17:27:40 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/**
 * It takes a string and returns a string with all the backslashes removed
 * 
 * @param str The string to be lexed.
 * 
 * @return A string with the escape characters removed.
 */
char	*ft_lexer(char *str)
{
	int		i;
	int		j;
	char	*line;
	
	i = 0;
	j = 0;
	line = ft_strnew(ft_strlen(str));;
	while (str[i])
	{
		if (str[i] == '\\')
			i++;
		line[j++] = str[i++];
	}
	return (line);
}
