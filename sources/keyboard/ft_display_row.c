/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_row.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 12:42:10 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/11 16:51:04 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

ssize_t	ft_display_row(t_term *t, ssize_t c_row)
{
	ssize_t	row;

	row = 0;
	if ((t->start_row + c_row) > t->ws_row) // THis works for cursor movement
		row = t->start_row - (t->total_row - c_row);
	else
		row = c_row + t->start_row;
	return (row);
}

ssize_t	ft_display_row_v2(t_term *t, ssize_t c_row)
{
	ssize_t	row;

	row = 0;
	if ((t->start_row + c_row) > t->ws_row) // THis works for cursor movement
		row = t->ws_row;
	else
		row = c_row + t->start_row;
	return (row);
}
