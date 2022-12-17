/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:38:31 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/17 16:14:40 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	ft_bslash_null(char *buff, ssize_t pos)
{
	ssize_t	count;

	if (!pos)
		return (0);
	count = pos - 1;
	while (count && buff[count] == '\\')
		count--;
	if (!count)
		count++;
	if (((pos - 1) - count) % 2)
		return (1);
	return (0);
}

static void	ft_quote_newline_parse(char *buff)
{
	int		i;
	int		k;
	char	quote;

	k = -1;
	quote = 0;
	while (buff[++k])
	{
		if (buff[k] == '\n' && ft_bslash_null(buff, k))
			i = k + 1;
		else if ((buff[k] == S_QUO || buff[k] == D_QUO) \
		&& !ft_bslash_null(buff, k))
		{
			if (!quote)
				quote = buff[k];
			else if (quote == buff[k])
				quote = 0;
			i = k + 1;
		}
		else
			i = k;
		if (i != k)
			ft_memmove((void *)&buff[k], (void *)&buff[i], \
			ft_strlen(&buff[i]) + 1);
	}
}

static void	ft_bslash_parse(char *buff)
{
	int		len;

	len = ft_strlen(buff);
	while (len >= 0)
	{
		if (buff[len] == '\\' && !ft_bslash_null(buff, len))
			ft_memmove((void *)&buff[len], (void *)&buff[len + 1], \
			ft_strlen(&buff[len + 1]) + 1);
		len--;
	}
}

void	ft_quote_blash_removal(char *buff)
{
	ft_quote_newline_parse(buff);
	ft_bslash_parse(buff);
}
