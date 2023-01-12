/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_iter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:50:44 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/23 13:33:08 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"

/**
 * Iterate through the vector and call the function f on each element
 * 
 * @param src The vector to iterate over.
 * @param f The function to be called on each element.
 * 
 * @return A pointer to the element at the given index.
 */
void	ft_vec_iter(t_vec *src, void (*f) (void *))
{
	void	*ptr;
	size_t	i;

	if (!src || !src->memory)
		return ;
	i = 0;
	while (i < src->len)
	{
		ptr = ft_vec_get(src, i);
		f(ptr);
		i++;
	}
}
