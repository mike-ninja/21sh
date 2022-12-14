/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_utils_more.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:38:17 by jniemine          #+#    #+#             */
/*   Updated: 2022/12/14 16:51:18 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	increment_whitespace(char **line)
{
	int	i;

	i = 0;
	while (*line && (*line)[i] && is_ws((*line)[i]))
		++i;
	*line += i;
	return (i);
}

int	increment_not_whitespace(char **line)
{
	int	i;

	i = 0;
	while ((*line)[i] && !is_ws((*line)[i]))
		++i;
	*line += i;
	return (i);
}
