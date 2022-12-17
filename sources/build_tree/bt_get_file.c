/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_get_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:41:30 by jniemine          #+#    #+#             */
/*   Updated: 2022/12/16 21:29:02 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char	*get_file(char *value)
{
	int		start;
	int		end;
	char	*res;

	start = 1;
	if (!value)
		return (NULL);
	if (value[start] == value[start - 1] || value[start] == '&')
		++start;
	while (value[start] && is_ws(value[start]))
		++start;
	end = start;
	while (value[end] && !is_ws(value[end]))
		++end;
	if (end <= start)
		return (NULL);
	res = ft_strsub(value, start, end - start);
	return (res);
}
