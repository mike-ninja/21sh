/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:05:26 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/23 13:23:57 by mbarutel         ###   ########.fr       */
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
	char	*line;
	
	i = 0;
	str = ft_skip_space(str);
	line = ft_strnew(ft_strlen(str));
	while (*str)
	{
		if (*str == '\\')
			str += 2;
		if (*str)
		{	
			line[i++] = *str++;
			if (line[i] == ' ')
			{
				str = ft_skip_space(str);
				if (*str)
					line[i++] = ' ';
			}
		}
	}
	return (line);
}

