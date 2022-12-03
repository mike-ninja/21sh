/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:05:26 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/03 18:37:08 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	ft_bslash_qoute_skip(char **str, char *quote)
{
	if (*(*str) == '\\')
	{
		(*str)++;
		if (*(*str) && *(*str) == '\n')
			(*str)++;
	}
	else if (*(*str) == '\'' || *(*str) == '\"')
	{
		(*str)++;
		if (!*quote)
			*quote = *(*str - 1);
		else if (*quote == *(*str - 1))
			*quote = 0;
	}
}

void	ft_lexer(char *str, char **line) // Needs to handle quote
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	str = ft_skip_space(str);
	if (str)
		*line = ft_strnew(ft_strlen(str));
	else
		*line = NULL;
	while (str && *str)
	{
		ft_bslash_qoute_skip(&str, &quote);
		if (*str)
		{
			(*line)[i++] = *str++;
			if (*str == ' ' && !quote)
			{
				str = ft_skip_space(str);
				if (*str)
					(*line)[i++] = ' ';
			}
		}
	}
	// ft_putendl(*line);
}
