/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_find_argument.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:13:39 by jakken            #+#    #+#             */
/*   Updated: 2023/01/09 15:37:03 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	operator_len(char *op)
{
	if (is_seperator(*op))
	{
		if (op[0] == '>' && ((op[1] == '>' || op[1] == '&')
				|| (op[0] == '<' && (op[1] == '<' || op[1] == '&'))))
			return (2);
		else if ((op[0] == '>' || op[0] == '<')
			&& op[1] == '&' && op[2] == '-')
			return (3);
		return (1);
	}
	return (0);
}

static void	traverse_to_end(char *line, int *end)
{
	while (line[*end] && ft_isspace(line[*end]))
		++(*end);
	while (line[*end] && !ft_isspace(line[*end]) && !is_seperator(line[*end]))
		++(*end);
}

static char	*tok_if_redir(char *line, int *i, int *start, int *end)
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
		traverse_to_end(line, end);
		return (ft_strsub(line, *start, *end - *start));
	}
	return (NULL);
}

static void	collect_digits(char *line, int *digits, int *end)
{
	while (ft_isdigit(line[*end - *digits]))
		++(*digits);
	if (*end - (*digits) == 0 || ft_isspace(line[*end - (*digits)]))
		*end -= (*digits);
}

char	*find_argument(char *line, int *i, int *start, int *end)
{
	char	*ret;
	int		digits;
	char	quote;

	quote = 0;
	digits = 1;
	ret = tok_if_redir(line, i, start, end);
	if (*end == -1)
		return (NULL);
	if (ret)
		return (ret);
	if (!is_seperator(line[*end]))
	{
		while ((line[*end] && !is_seperator(line[*end])) || quote)
			tok_quote_flag(line, end, &quote);
		if ((line[*end] == '>' || line[*end] == '<') && (*end) > 0)
			collect_digits(line, &digits, end);
		else if (*end > 0 && is_seperator(line[*end])/* && is_seperator(*end > 0 && line[*end])*/)
		{
			if (test_if_error(&line[*end + 1]))
			{
				*end = -1;
				return (NULL);
			}
			--(*end);
		}
	}
	else
		*end += operator_len(&line[*end]);
	if (*end == *start)
		++(*end);
	return (ft_strsub(line, *i, *end - *i));
}
