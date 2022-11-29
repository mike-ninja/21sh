/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:05:26 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/29 14:01:45 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/**
 * It skips over a backslash and the following newline, if any.
 * 
 * @param str The string to be parsed.
 */
static void	ft_bslash_skip(char **str)
{
	if (*(*str) == '\\')
	{
		(*str)++;
		if (*(*str) && *(*str) == '\n')
			(*str)++;
	}
}

/**
 * It takes a string and a pointer to a string, and it copies the string into
 * the pointer to a string, skipping spaces and backslashes
 * 
 * @param str the string to be parsed
 * @param line the address of a pointer to a character. The string placed in
 * this character's address will be placed in the array of strings.
 */
void	ft_lexer(char *str, char **line) // Needs to handle quote
{
	int		i;

	i = 0;
	str = ft_skip_space(str);
	*line = ft_strnew(ft_strlen(str));
	while (*str)
	{
		ft_bslash_skip(&str);
		if (*str)
		{	
			(*line)[i++] = *str++;
			if ((*line)[i] == ' ')
			{
				str = ft_skip_space(str);
				if (*str)
					(*line)[i++] = ' ';
			}
		}
	}
}
