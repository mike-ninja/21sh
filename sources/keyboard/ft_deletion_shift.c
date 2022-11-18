/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deletion_shift.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:21:37 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/11 15:46:00 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	ft_deletion_shift(t_term *t, int mode)
{
	ssize_t	index_cpy;

	if (mode == BCK)
		t->index--;
	index_cpy = t->index;
	t->inp[index_cpy] = '\0';
	while (&t->inp[index_cpy] < &t->inp[t->bytes])
	{
		t->inp[index_cpy] = t->inp[index_cpy] ^ t->inp[index_cpy + 1];
		t->inp[index_cpy + 1] = t->inp[index_cpy] ^ t->inp[index_cpy + 1];
		t->inp[index_cpy] = t->inp[index_cpy] ^ t->inp[index_cpy + 1];
		index_cpy++;
	}
	t->bytes--;
}
