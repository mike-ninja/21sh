/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 09:41:05 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/16 16:21:15 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	print_error(int check)
{
	if (check == 1)
		ft_putstr_fd("42sh: No editor found. Please set FCEDIT or EDITOR.", 2);
	else if (check == 2)
		ft_putstr_fd("42sh: Could not open file for editing.", 2);
	else if (check == 3)
	{
		ft_putstr_fd("42sh: Error malloc, in ft_strsplit() from ft_fc().", 2);
		exit(1);
	}
	return (0);
}

static char	*get_editor(char **env)
{
	char *editor;

	editor = getenv("FCEDIT");
	if (!editor)
		editor = getenv("EDITOR");
	if (!editor)
		editor = search_bin("vim", env);
	if (!editor)
		editor = search_bin("vi", env);
	if (!editor)
		editor = search_bin("ed", env);
	if (!editor)
		return (NULL);
	return (editor);
}

static void	init_filename(char ***filename, char *editor)
{
	(*filename) = (char **)malloc(sizeof(char *) * 3);
	if (!(*filename))
	{
		ft_putstr_fd("42sh: Error malloc, init_filename() from ft_fc().", 2);
		exit(1);
	}
	(*filename)[0] = editor;
	(*filename)[1] = ft_strdup("/tmp/ft_fc");
	(*filename)[2] = NULL;
}

static char	**open_editor(char *editor, t_session *sesh)
{
	int		fd;
	char	**filename;

	init_filename(&filename, editor);
	fd = open(filename[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		print_error(2);
		return (NULL);
	}
	ft_putstr_fd(sesh->term->history_arr[sesh->term->history_size - 2], fd);
	if (fork_wrap() == 0)
	{
		execve(editor, filename, sesh->env);
		exit(1);
	}
	wait(0);
	close(fd);
	return (filename);
}

static char	*ft_strupdate(char *s1, const char *s2)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	if (!ret)
		return (NULL);
	ft_strdel(&s1);
	return (ret);
}

static int	read_file(char ***cmd, char **filename, char **ret_cmd)
{
	int		fd;
	char	*new_cmd;

	fd = open(filename[1], O_RDONLY);
	if (fd == -1)
		return (print_error(2));
	while (get_next_line(fd, &new_cmd) > 0)
	{
		if (!(*ret_cmd))
			*ret_cmd = ft_strdup(new_cmd);
		else
		{
			*ret_cmd = ft_strupdate(*ret_cmd, "\n");
			*ret_cmd = ft_strupdate(*ret_cmd, new_cmd);
		}
		ft_strdel(&new_cmd);
	}
	ft_strdel(&new_cmd);
	ft_freeda((void ***)cmd, calc_chptr(*cmd));
	ft_putendl(*ret_cmd);
	*cmd = ft_strsplit(*ret_cmd, ' ');
	if (!*cmd)
		print_error(3);
	close(fd);
	return (1);
}

static void	overwrite_history(t_session *sesh, char *ret_cmd)
{
	ft_strdel(&sesh->term->history_arr[sesh->term->history_size - 1]);
	sesh->term->history_arr[sesh->term->history_size - 1] = ft_strdup(ret_cmd);
}

static int	check_flags(t_session *sesh, char ***cmd)
{
	if (*cmd && ft_strnequ((*cmd)[1], "-s", 2))
	{
		//this is for history
		ft_strdel(&sesh->term->history_arr[sesh->term->history_size - 1]);
		sesh->term->history_arr[sesh->term->history_size - 1] = ft_strdup(sesh->term->history_arr[sesh->term->history_size - 2]);

		//execute the command too
		ft_freeda((void ***)cmd, calc_chptr(*cmd));
		ft_putendl(sesh->term->history_arr[sesh->term->history_size - 2]);
		*cmd = ft_strsplit(sesh->term->history_arr[sesh->term->history_size - 2], ' ');
		if (!*cmd)
			print_error(3);
		return (1);
	}
	else if ((*cmd && ft_strnequ((*cmd)[1], "-l", 2)) || ft_strnequ((*cmd)[1], "-ln", 3) || ft_strnequ((*cmd)[1], "-nl", 3))
	{
		int i;

		i = sesh->term->history_size - 16;
		if (ft_strchr((*cmd)[1], 'n'))
		{
			while (sesh->term->history_arr[i])
			{
				ft_printf("\t%s\n", sesh->term->history_arr[i]);
				i++;
			}
		}
		else
		{
		/* Printing the history. */
			while (sesh->term->history_arr[i])
			{
				ft_printf("%-8d %s\n", i + 1, sesh->term->history_arr[i]);
				i++;
			}
		}
		return (0);
	}
	else if (*cmd && ft_strnequ((*cmd)[1], "-rl", 3))
	{
		int i;

		i = sesh->term->history_size - 16;
		while (i  < (int)sesh->term->history_size)
		{
			ft_printf("%-8d %s\n", i + 1, sesh->term->history_arr[i]);
			i++;
		}
		return (0);
	}
	else
		ft_putendl_fd("42sh: fc: invalid option\nfc: usage: fc [-e editor] [first] [last] or fc -l [first] [last] or fc -s [pat=rep] [command]", 2);
	return (0);
}

int	ft_fc(t_session *sesh, char ***cmd)
{
	char	*editor;
	char	**filename;
	char	*ret_cmd;
	int		ret;

	if ((*cmd && !(*cmd)[1]) || (*cmd && ft_strnequ((*cmd)[1], "-e", 2) && (*cmd)[2]))
	{
		if ((*cmd && ft_strnequ((*cmd)[1], "-e", 2) && (*cmd)[2]))
			editor = search_bin((*cmd)[2], sesh->env);
		else
			editor = get_editor(sesh->env);
		if (!editor)
			return (print_error(1));
		filename = open_editor(editor, sesh);
		if (!filename)
			return (0);
		ret_cmd = NULL;
		if (!read_file(cmd, filename, &ret_cmd))
			return (0);
		ft_expansion(sesh, *cmd);
		overwrite_history(sesh, ret_cmd);
		ft_strdel(&ret_cmd);
		ft_freeda((void ***)&filename, calc_chptr(filename));
		ret = 1;
	}
	else
		ret = check_flags(sesh, cmd);
	return (ret);
}
