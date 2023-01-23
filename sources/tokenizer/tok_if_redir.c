/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_if_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 17:11:18 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/23 16:46:23 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
static int	does_redir_have_dest(char *line, int *end)
{
	int i;

	i = 0;
	ft_printf("LINE: %s\n", &line[*end]);
	while (line[*end + i] && !is_seperator(line[*end + i]))
		++i;
	if (i > 0)
		return (1);
	if (is_seperator(line[*end]))
	{
		ft_printf("WHY\n");
		*(line + (*end + 1)) = '\0';
		ft_err_print(NULL, "syntax error near unexpected token",
			line + *end, 2);
		ft_printf("NOT\n");
	}
	else
	{
		ft_err_print(NULL, "syntax error near unexpected token",
			"`newline'", 2);
	}
	return (0);
}
*/

static int	traverse_to_end(char *line, int *end)
{
	while (line[*end] && ft_isspace(line[*end]))
		++(*end);
	if (redir_error(&line[*end]))
	{
		*end = -1;
		return (1);
	}
	while (line[*end] && !ft_isspace(line[*end]) && !is_seperator(line[*end]))
		++(*end);
	while (ft_isspace(line[*end]))
		++(*end);
	return (0);
}

char	*tok_if_redir(char *line, int *i, int *start, int *end)
{
	int	digits;

	digits = 0;
	while (ft_isdigit(line[*i + digits]))
		++digits;
	if (line[*i + digits] == '>' || line[*i + digits] == '<')
	{
		*start = *i;
		*i = *i + digits;
		*end = *i + digits + 1;
		if (line[*end] == '<' || line[*end] == '>' || line[*end] == '&')
			++(*end);
		if (*end && line[(*end) - 1] == '&' && line[*end] == '-')
			return (ft_strsub(line, *start, (++(*end)) - *start));
		if (redir_error(&line[*end]))
		{
			*end = -1;
			return (NULL);
		}
		if (traverse_to_end(line, end))
			return (NULL);
		return (ft_strsub(line, *start, *end - *start));
	}
	return (NULL);
}
