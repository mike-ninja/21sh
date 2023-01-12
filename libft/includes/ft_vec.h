/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:46:48 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/23 13:31:24 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VEC_H
# define FT_VEC_H

# include "libft.h"

typedef struct s_vec
{
	size_t			len;
	unsigned char	*memory;
	size_t			elem_size;
	size_t			alloc_size;
}	t_vec;

void	ft_vec_free(t_vec *src);
int		ft_vec_push(t_vec *src, void *elem);
void	*ft_vec_get(t_vec *src, size_t index);
void	ft_vec_iter(t_vec *src, void (*f) (void *));
int		ft_vec_resize(t_vec *src, size_t target_size);
void	ft_vec_sort(t_vec *src, int (*f)(void *, void *));
int		ft_vec_new(t_vec *src, size_t init_len, size_t elem_size);
int		ft_vec_from(t_vec *dst, void *src, size_t len, size_t elem_size);

#endif
