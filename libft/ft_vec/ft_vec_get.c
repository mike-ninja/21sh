/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:50:42 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/23 13:33:04 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"

/**
 * ft_vec_get() returns a pointer to the element at index `index` in the 
 * vector `src`.
 * 
 * @param src The vector to get the element from.
 * @param index The index of the element you want to get.
 * 
 * @return A pointer to the element at the given index.
 */
void	*ft_vec_get(t_vec *src, size_t index)
{
	if (index >= src->len || !src || !src->memory)
		return (NULL);
	return ((void *)&src->memory[src->elem_size * index]);
}
