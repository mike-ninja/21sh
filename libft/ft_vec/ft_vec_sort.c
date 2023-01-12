/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:50:52 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/23 13:33:20 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"

static void	memswap8bytes(char *a, char *b)
{
	if (a == b)
		return ;
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

static void	memswap(char *a, char *b, size_t bytes)
{
	size_t	i;

	if (!a || !b)
		return ;
	i = 0;
	while (i < bytes)
	{
		memswap8bytes(&a[i], &b[i]);
		i++;
	}
}

static void	vec_sort_recurse(t_vec *src, long low, long high, \
int (*f)(void *, void *))
{
	long	pivot;
	long	a;
	long	b;

	if (low >= high)
		return ;
	pivot = low;
	a = low;
	b = high;
	while (a < b)
	{
		while (a <= high && f(ft_vec_get(src, a), ft_vec_get(src, pivot)) <= 0)
			a++;
		while (b >= low && f(ft_vec_get(src, b), ft_vec_get(src, pivot)) > 0)
			b--;
		if (a < b)
			memswap(ft_vec_get(src, a), ft_vec_get(src, b), src->elem_size);
	}
	memswap(ft_vec_get(src, pivot), ft_vec_get(src, b), src->elem_size);
	vec_sort_recurse(src, low, b - 1, f);
	vec_sort_recurse(src, b + 1, high, f);
}

/**
 * It sorts the vector by
 * recursively dividing the vector into two parts, sorting each part, and
 * then merging the two parts together
 * 
 * @param src The vector to sort
 * @param f The function to use to compare two elements.
 * 
 * @return Nothing.
 */
void	ft_vec_sort(t_vec *src, int (*f)(void *, void *))
{
	if (!src || !src->memory)
		return ;
	vec_sort_recurse(src, 0, src->len - 1, f);
}
