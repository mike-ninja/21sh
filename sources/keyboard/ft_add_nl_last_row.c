/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_nl_last_row.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 13:42:45 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/29 16:34:38 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It adds a newline address to the array of newline addresses
 *
 * @param t the term structure
 * @param pos The position of the newline character in the input string.
 */
void	ft_add_nl_last_row(t_term *t, ssize_t pos)
{
	int		index;
	char	**n_arr;

	index = -1;
	n_arr = NULL;
	if (!t->nl_addr)
	{
		t->nl_addr = (char **)ft_memalloc(sizeof(char *) * 2);
		t->nl_addr[++index] = &t->inp[pos];
		t->nl_addr[++index] = NULL;
	}
	else
	{
		n_arr = (char **)ft_memalloc(sizeof(char *) \
			* (size_t)(t->total_row + 2));
		while (t->nl_addr[++index])
			n_arr[index] = t->nl_addr[index];
		n_arr[index++] = &t->inp[pos];
		n_arr[index] = NULL;
		ft_memdel((void **)&t->nl_addr);
		t->nl_addr = n_arr;
	}
}
