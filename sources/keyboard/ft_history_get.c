/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_get.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:56:28 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/18 17:06:52 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	ft_history_get(t_term *t)
{
	char	*buf;
	int		fd;

	ft_vec_new(&t->v_history, 0, sizeof(char) * 256);
	t->history_file = ft_history_file_get();
	fd = open(t->history_file, O_RDONLY | O_CREAT, 0644);
	if (fd)
	{
		buf = NULL;
		while (get_next_line(fd, &buf) > 0) // this needs to be checkoing for \0, not \n. i think
		{
			ft_vec_push(&t->v_history, buf); //&buf or not &buf? valgrind will say invalid read if not but text file font will be strange?
			ft_strdel(&buf);
		}
		ft_strdel(&buf);
		close(fd);
	}
}
