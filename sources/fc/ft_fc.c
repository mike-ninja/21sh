/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 09:41:05 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/24 13:26:53 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

//add to libft
static char	*ft_strupdate(char *s1, const char *s2)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	if (!ret)
		return (NULL);
	ft_strdel(&s1);
	return (ret);
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


//in other file
static int	null_check_first(t_session *sesh, char *cmd)
{
	int start;

	if (ft_atoi(cmd) == 0)
	{
		start = sesh->term->history_size - 3;
		sesh->term->history_size -= 1;
	}
	else
		start = ft_atoi(cmd) - 2;
	if (start < -1)
	{
		start = sesh->term->history_size + start;
		if (start < 0)
			start = -1;
	}
	return (start);
}

static int	null_check_last(t_session *sesh, char *cmd)
{
	int last;

	if (ft_atoi(cmd) == 0)
		last = sesh->term->history_size;
	else
		last = ft_atoi(cmd) + 1;
	if (last <= 0)
		last = sesh->term->history_size;
	return (last);
}

static int	get_start(t_session *sesh, char ***cmd, int e)
{
	int start;

	if ((*cmd)[0 + e] && (*cmd)[1 + e] && !(*cmd)[2 + e])
		start = null_check_first(sesh, (*cmd)[1 + e]);
	else if ((*cmd)[0 + e] && (*cmd)[1 + e] && (*cmd)[2 + e])
	{
		start = null_check_first(sesh, (*cmd)[1 + e]);
		sesh->term->history_size = null_check_last(sesh, (*cmd)[2 + e]);
	}
	else if (sesh->term->history_size > FC_LEN)
		start = sesh->term->history_size - FC_LEN;
	else
		start = -1;
	return (start);
}






static char	**open_editor(char *editor, t_session *sesh, char ***cmd, int e)
{
	int		fd;
	char	**filename;

	init_filename(&filename, editor);
	fd = open(filename[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		fc_print_error(2);
		return (NULL);
	}
	// ft_putstr_fd(sesh->term->history_arr[sesh->term->history_size - 2], fd);
	int start = get_start(sesh, cmd, e);
	while (++start < (int)sesh->term->history_size - 1)
	{
		ft_putstr_fd(sesh->term->history_arr[start], fd);
		write(fd, "\n", 1);
	}
	if (fork_wrap() == 0)
	{
		execve(editor, filename, sesh->env);
		exit(1);
	}
	wait(0);
	close(fd);
	return (filename);
}

static int	read_file(char ***cmd, char **filename, char **ret_cmd)
{
	int		fd;
	char	*new_cmd;

	(void)cmd;
	fd = open(filename[1], O_RDONLY);
	if (fd == -1)
		return (fc_print_error(2));
	while (get_next_line(fd, &new_cmd) > 0)
	{
		if (!(*ret_cmd))
			*ret_cmd = ft_strdup(new_cmd);
		else
		{
			*ret_cmd = ft_strupdate(*ret_cmd, ";");
			*ret_cmd = ft_strupdate(*ret_cmd, new_cmd);
		}
		ft_strdel(&new_cmd);
	}
	ft_strdel(&new_cmd);
	ft_freeda((void ***)cmd, calc_chptr(*cmd));
	ft_putendl(*ret_cmd);
	/* *cmd = ft_strsplit(*ret_cmd, ' ');
	if (!*cmd)
		fc_print_error(3); */
	close(fd);
	return (1);
}

static void	overwrite_history(t_session *sesh, char *ret_cmd)
{ //take away the semi colon of ret_cmd
	ft_strdel(&sesh->term->history_arr[sesh->term->history_size - 1]);
	sesh->term->history_arr[sesh->term->history_size - 1] = ft_strdup(ret_cmd);
}

static int	no_flag_or_e_flag(t_session *sesh, char ***cmd, int e)
{
	char	*editor;
	char	**filename;
	char	*ret_cmd;

	if ((*cmd && ft_strnequ((*cmd)[1], "-e", 2) && (*cmd)[2]))
		editor = search_bin((*cmd)[2], sesh->env);
	else
		editor = get_editor(sesh->env);
	if (!editor)
		return (fc_print_error(1));
	filename = open_editor(editor, sesh, cmd, e);
	if (!filename)
		return (0);
	ret_cmd = NULL;
	if (!read_file(cmd, filename, &ret_cmd))
		return (0);

	overwrite_history(sesh, ret_cmd);

	char	*new;
	t_treenode *head;
	t_token *tokens;

	tokens = NULL;
	new = ft_strtrim(ret_cmd);
	ft_freeda((void ***)&filename, calc_chptr(filename));
	tokens = chop_line(new, tokens, 1);
	head = build_tree(tokens);
	if (head && ((t_semicolon *)head)->left)
		exec_tree(head, &sesh->env, sesh->terminal, sesh);
	free_node(head);
	free_tokens(&tokens);
	ft_strdel(&ret_cmd);
	return (0);
}

/* static int	error_check(char ***cmd, int *start, int *last)
{
	if (!(*cmd)[1])
	{
		*start = -1;
		*last = -1;
	}
	else if ((*cmd)[1] && !(*cmd)[2])
	{
		*start = ft_atoi((*cmd)[1]) - 2;
		*last = ft_atoi((*cmd)[1]) + 1;
	}
	else if ((*cmd)[1] && (*cmd)[2] && !(*cmd)[3])
	{
		*start = ft_atoi((*cmd)[1]) - 2;
		*last = ft_atoi((*cmd)[2]) + 1;
	}
	else
		return (0);
	return (1);
} */

int	ft_fc(t_session *sesh, char ***cmd)
{
	int		ret;
	int		e;

	e = 0;
	if (ft_strnequ((*cmd)[1], "-e", 2))
		e = 2;
	if ((*cmd && !(*cmd)[1]) \
		|| (*cmd && (*cmd)[1] && (*cmd)[1] && (*cmd)[1][0] == '-' && ft_isdigit((*cmd)[1][1])) \
		|| (*cmd && e ))
		ret = no_flag_or_e_flag(sesh, cmd, e);
	else
		ret = fc_check_flags(sesh, cmd);
	return (ret);
}
