/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_if_logical.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:21:17 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/22 22:19:08 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char	*tok_if_logical(char *line, int *i, int *start, int *end)
{
	ft_printf("LINE: |%s|\n", &line[*i]);
	if ((line[*i] == '|' && line[*i + 1] == '|')
		|| (line[*i] == '&' && line[*i + 1] == '&'))
	{
		*start = *i;
		*end = *start + 2;
		if (control_op_error(&line[*end - 1]))
		{
			*end = -1;
			return (NULL);
		}
		return (ft_strsub(line, *start, 2));
	}
	else if (line[*i] == '&')
	{
		ft_printf("ARE WE HERE\n");
		*start = *i;
		*end = *start + 1;
		if (control_op_error(&line[*end - 1]))
		{
			*end = -1;
			return (NULL);
		}
		return (ft_strsub(line, *start, 1));
	}
	return (NULL);
}
