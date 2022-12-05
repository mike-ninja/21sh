/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deletion_shift.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:21:37 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/29 17:11:08 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It deletes a character from the input string and shifts the rest of the
 * string to the left
 *
 * @param t the t_term struct
 * @param mode 0 for backspace, 1 for delete
 */
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
