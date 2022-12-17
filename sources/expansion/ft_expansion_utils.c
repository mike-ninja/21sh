/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:38:31 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/17 13:45:53 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	ft_qoute_handling(char *buff, int k, char *quote)
{
	int	i;

	i = k;
	if (!*quote)
		*quote = buff[k];
	else if (*quote == buff[k])
	{
		i++;
		if (buff[i] == '\'' || buff[i] == '\"')
			*quote = buff[i];
		else
			*quote = 0;
	}
	while (buff[i] && (buff[i] == *quote))
		i++;
	return (i);
}

static int	blash_handling(char *buff, int k)
{
	int	i;

	i = k + 1;
	if (buff[i] == '\n')
		i++;
	return (i);
}

static int	newline_handling(char *buff, int *k)
{
	int	i;

	i = *k;
	if (*k && buff[*k - 1] == '\\')
	{
		(*k)--;
		i++;
	}
	return (i);
}

void	ft_quote_blash_removal(char *buff)
{
	int		k;
	int		i;
	char	quote;

	k = -1;
	quote = 0;
	while (buff[++k])
	{
		if (buff[k] == '\\')
			i = blash_handling(buff, k);
		else if (buff[k] == '\n')
			i = newline_handling(buff, &k);
		else if ((buff[k] == '\'' || buff[k] == '\"'))
			i = ft_qoute_handling(buff, k, &quote);
		else
			i = k;
		ft_memmove((void *)&buff[k], (void *)&buff[i], ft_strlen(&buff[i]) + 1);
	}
}
