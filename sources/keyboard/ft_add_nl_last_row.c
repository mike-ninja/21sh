/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_nl_last_row.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 13:42:45 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/11 16:08:31 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	ft_add_nl_last_row(t_term *t, ssize_t pos)
{
	int		index;
	char	**fresh_array;

	index = -1;
	fresh_array = NULL;
	if (!t->nl_addr)
	{
		t->nl_addr = (char **)ft_memalloc(sizeof(char *) * 2);
		t->nl_addr[++index] = &t->inp[pos];
		t->nl_addr[++index] = NULL;
	}
	else
	{
		fresh_array = (char **)ft_memalloc(sizeof(char *) * (size_t)(t->total_row + 2));
		while (t->nl_addr[++index])
			fresh_array[index] = t->nl_addr[index];
		fresh_array[index++] = &t->inp[pos];
		fresh_array[index] = NULL;
		ft_memdel((void **)&t->nl_addr);
		t->nl_addr = fresh_array;
	}
}
