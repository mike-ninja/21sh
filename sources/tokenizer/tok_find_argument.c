/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_find_argument.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:13:39 by jakken            #+#    #+#             */
/*   Updated: 2023/01/18 16:21:16 by mbarutel         ###   ########.fr       */
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

static void	collect_digits(char *line, int *digits, int *end)
{
	while (ft_isdigit(line[*end - *digits]))
		++(*digits);
	if (*end - (*digits) == 0 || ft_isspace(line[*end - (*digits)]))
		*end -= (*digits);
}

static int	test_validity(char *line, int *end)
{
	if (*end > 0 && is_seperator(line[*end]))
	{
		if (test_if_error(&line[*end]))
		{
			*end = -1;
			return (1);
		}
	}
	return (0);
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
		while (line[*end] && (!is_seperator(line[*end]) || quote))
			tok_quote_flag(line, end, &quote);
		if ((line[*end] == '>' || line[*end] == '<') && (*end) > 0)
			collect_digits(line, &digits, end);
		else if (test_validity(line, end))
			return (NULL);
	}
	else
		*end += operator_len(&line[*end]);
	if (*end == *start)
		++(*end);
	return (ft_strsub(line, *i, *end - *i));
}
