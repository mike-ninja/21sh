/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_write_to_file.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:59:21 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/04 19:14:14 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It writes the history to the file
 *
 * @param t The terminal structure.
 */
void	ft_history_write_to_file(t_term *t)
{
	size_t	cpy;
	int		fd;

	fd = open(t->history_file, O_WRONLY | O_TRUNC);
	if (fd)
	{
		cpy = 0;
		if (t->v_history.len > 1024)
			cpy = t->v_history.len % 1024;
		while (cpy < t->v_history.len)
		{
			ft_putendl_fd((char *)ft_vec_get(&t->v_history, cpy), fd);
			cpy++;
		}
		close(fd);
	}
	ft_strdel(&t->history_file);
	ft_vec_free(&t->v_history);
}
