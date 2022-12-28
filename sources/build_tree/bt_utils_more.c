/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_utils_more.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:38:17 by jniemine          #+#    #+#             */
/*   Updated: 2022/12/28 19:47:27 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	increment_whitespace(char **line)
{
	int	i;

	i = 0;
	while (*line && (*line)[i] && ft_isspace((*line)[i]))
		++i;
	*line += i;
	return (i);
}

int	increment_not_whitespace(char **line)
{
	int	i;

	i = 0;
	while ((*line)[i] && !ft_isspace((*line)[i]))
		++i;
	*line += i;
	return (i);
}
