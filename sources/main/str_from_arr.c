/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_from_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 18:12:29 by jakken            #+#    #+#             */
/*   Updated: 2022/12/15 17:14:10 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char	*str_from_arr(char **arr)
{
	char	*str;
	int		len;
	int		i;

	len = 0;
	i = 0;
	str = NULL;
	while (arr[i])
	{
		len += ft_strlen(arr[i]);
		++i;
	}
	str = ft_memalloc(len + i + 2);
	i = 0;
	while (arr[i])
	{
		ft_strcat(str, arr[i]);
		if (arr[i + i])
			ft_strcat(str, " ");
		++i;
	}
	return (str);
}
