/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_resize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:50:50 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/23 13:33:15 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"

/**
 * It resizes a vector to a
 * given size
 * 
 * @param src The vector to resize.
 * @param target_size The new size of the vector.
 * 
 * @return The new size of the vector.
 */
int	ft_vec_resize(t_vec *src, size_t target_size)
{
	t_vec	dst;

	if (!src)
		return (-1);
	else if (!src->memory)
		return (ft_vec_new(src, target_size, src->elem_size));
	else if (ft_vec_new(&dst, target_size, src->elem_size) < 0)
		return (-1);
	ft_memcpy(dst.memory, src->memory, src->alloc_size);
	dst.len = src->len;
	ft_vec_free(src);
	*src = dst;
	return (target_size);
}
