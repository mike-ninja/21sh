/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:38:31 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/17 17:31:25 by mbarutel         ###   ########.fr       */
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
	if ((pos - count) % 2)
		return (1);
	return (0);
}

void	ft_quote_blash_removal(char *buff)
{
	int		len;
	char	quote;

	quote = 0;
	len = ft_strlen(buff);
	while (len >= 0)
	{
		if ((buff[len] == S_QUO || buff[len] == D_QUO))
		{
			if (!len || buff[len - 1] != '\\' || !ft_bslash_null(buff, len)) // problem here echo \'mike
			{	
				if (!quote)
					quote = buff[len];
				else if (quote == buff[len])
					quote = 0;
				ft_memmove((void *)&buff[len], (void *)&buff[len + 1], ft_strlen(&buff[len + 1]) + 1);
			}
		}
		else if (buff[len] == '\\')
		{
			if (!quote && ft_bslash_null(buff, len))
				ft_memmove((void *)&buff[len], (void *)&buff[len + 1], ft_strlen(&buff[len + 1]) + 1);
			else if (quote == D_QUO && !ft_bslash_null(buff, len))
				ft_memmove((void *)&buff[len], (void *)&buff[len + 1], ft_strlen(&buff[len + 1]) + 1);
		}
		else if (buff[len] == '\n' && len && buff[len - 1] == '\\' && !ft_bslash_null(buff, len))
			ft_memmove((void *)&buff[len], (void *)&buff[len + 1], ft_strlen(&buff[len + 1]) + 1);
		len--;
	}
}
