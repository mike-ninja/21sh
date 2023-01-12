/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:50:46 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/23 13:32:39 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"

/**
 * It creates a new vector
 * 
 * @param dst the vector to initialize
 * @param init_len The initial length of the vector.
 * @param elem_size The size of each element in the vector.
 * 
 * @return The size of the allocated memory.
 */
int	ft_vec_new(t_vec *dst, size_t init_len, size_t elem_size)
{
	if (!dst || elem_size == 0)
		return (-1);
	dst->alloc_size = init_len * elem_size;
	dst->len = 0;
	dst->elem_size = elem_size;
	if (init_len == 0)
		dst->memory = NULL;
	else
	{
		dst->memory = malloc(dst->alloc_size);
		if (!dst->memory)
		{
			ft_putendl_fd("error, malloc vec_new()", 2);
			exit(1);
		}
	}
	return (dst->alloc_size);
}
