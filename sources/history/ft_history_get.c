/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_get.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:56:28 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/11 12:51:35 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
 * It reads the history file and stores it in a ft_vector
 *
 * @param t the terminal structure
 */
static void	count_history(t_term *t)
{
	int		fd;
	char	*line;
	int		size;

	fd = open(t->history_file, O_RDONLY | O_CREAT, 420);
	size = 0;
	if (fd)
	{
		line = NULL;
		while (get_next_line(fd, &line) > 0)
		{
			size++;
			ft_strdel(&line);
		}
		ft_strdel(&line);
		close(fd);
	}
	t->history_size = size;
}

static char	*ft_history_file(char *str)
{
	char	cwd[BUFF_SIZE];
	char	*home;
	char	*file;

	home = getenv("HOME");
	if (home)
		return (ft_strjoin(home, str));
	file = getcwd(cwd, sizeof(cwd));
	return (ft_strjoin(file, str));
}

void	ft_history_get(t_term *t)
{
	char	*line;
	int		fd;
	int		i;

	t->history_file = ft_history_file("/.42sh_history");
	count_history(t);
	t->history_arr = (char **)malloc(sizeof(char *) * (t->history_size + 1));
	ft_bzero(t->history_arr, t->history_size + 1);
	i = 0;
	fd = open(t->history_file, O_RDONLY | O_CREAT, 420);
	if (fd)
	{
		line = NULL;
		while (get_next_line(fd, &line) > 0)
		{
			t->history_arr[i] = ft_strdup(line);
			i++;
			ft_strdel(&line);
		}
		ft_strdel(&line);
		close(fd);
		t->history_arr[i] = NULL;
		t->history_size = i;
	}
}
