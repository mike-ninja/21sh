/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_argument_until_seperator.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 20:47:08 by jakken            #+#    #+#             */
/*   Updated: 2022/12/13 21:08:52 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*	See if one of the characters from seperators array can be
	found before whitespace from the haystack */
static char	*is_infuture(char *haystack, char *seperators)
{
	int	i_sep;
	int	i_hay;

	i_sep = 0;
	i_hay = 0;
	while (haystack[i_hay] && !is_ws(haystack[i_hay]))
	{
		while (seperators[i_sep])
		{
			if (haystack[i_hay] == seperators[i_sep++])
				return (&haystack[i_hay]);
		}
		i_sep = 0;
		++i_hay;
	}
	while (haystack[i_hay] && is_ws(haystack[i_hay]))
		++i_hay;
	while (seperators[i_sep])
	{
		if (haystack[i_hay] == seperators[i_sep++])
			return (&haystack[i_hay]);
	}
	return (NULL);
}

static char	*find_argument_until_seperator(char *line, int *i,
			int *start, int *end)
{
	char	*infuture;

	infuture = is_infuture(&(line[(*i)]), "><");
	while ((line)[*i])
	{
		if (infuture || is_seperator((line)[*i]))
		{
			*start = *i;
			break ;
		}
		++(*i);
	}
	*end = *i;
	if (*i == 0 && infuture)
	{
		while ((line)[*i] && !is_ws((line)[*i]))
			++(*i);
		return (infuture);
	}
	else
		while ((line)[*end] && !is_ws((line)[*end]))
			++(*end);
	if (*i == 0 && is_seperator((line)[*i]))
		++(*i);
	return (NULL);
}
