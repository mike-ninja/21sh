/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_from.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:50:40 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/23 13:32:58 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"

/**
 * It creates a new vector from an existing array
 * 
 * @param dst The vector to copy the data into.
 * @param src The source memory to copy from.
 * @param len the number of elements to copy from src to dst
 * @param elem_size The size of each element in the vector.
 * 
 * @return The size of the allocated memory.
 */
int	ft_vec_from(t_vec *dst, void *src, size_t len, size_t elem_size)
{
	if (!dst || !src || len == 0 || elem_size == 0)
		return (-1);
	else if (ft_vec_new(dst, len, elem_size) < 0)
		return (-1);
	ft_memcpy(dst->memory, src, dst->alloc_size);
	dst->len = len;
	return (dst->alloc_size);
}
