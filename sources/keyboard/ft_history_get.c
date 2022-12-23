/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_get.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:56:28 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/20 15:43:42 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It reads the history file and stores it in a ft_vector
 *
 * @param t the terminal structure
 */
void	ft_history_get(t_term *t)
{
	char	*buf;
	int		fd;

	ft_vec_new(&t->v_history, 0, sizeof(char) * BUFF_SIZE);
	t->history_file = ft_history_file_get();
	fd = open(t->history_file, O_RDONLY | O_CREAT, 0644);
	if (fd)
	{
		buf = NULL;
		while (get_next_line(fd, &buf) > 0)
		{
			ft_vec_push(&t->v_history, buf);
			ft_strdel(&buf);
		}
		ft_strdel(&buf);
		close(fd);
	}
}
