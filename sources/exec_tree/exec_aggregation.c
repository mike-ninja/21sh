/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_aggregation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 20:26:00 by jakken            #+#    #+#             */
/*   Updated: 2022/12/17 00:14:20 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	is_nb(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		++str;
	}
	return (1);
}

//Test for input files also for <, make own function for that
/* If no write permission: 21sh: <filename>: Permission denied */
/* If dir: 21sh: <dirname>: Is a directory */
/* If does not exist just return and create */
int	test_file_access(char *file)
{
	struct stat buf;

	if (access(file, F_OK)) //exists
	{
		if (!access(file, W_OK)) // can be written to
			return (0);
	}
	else
		return (1); //Does not exist
	//Maybe protect stat? Can it fail if we know that file exists
	stat(file, &buf);
	if (buf.st_mode & S_IFDIR)
	{
		/* If dir: 21sh: <dirname>: Is a directory */
		//isdir error
	}
	if (buf.st_mode & S_IFREG)
	{
		//Does this confirm its a file?
	}
	//What type is fd file??
	//links to device on linux atleast

}

//Test access and isfile
static void	redir_to_file(t_aggregate *node, t_session *sesh)
{
	node->cmd = init_redir_wrap(ft_strdup(node->dest), node->cmd, RE_OUT_ONE, node->close_fd);
	exec_tree(node->cmd, &sesh->env, sesh->terminal, sesh);
}
/* allowed char after >& are / for path, $ for expand and ~ for expand, handle this in tokenizer, use fstat here to see if fd
	Path to /dev/fd/1 should work for example */
/* 2>&noexiset <- ambigious redirect >&noexist <- works*/
/* If source 1 and !digit !file dest is given create file, error handle dir */
void	exec_aggregate(t_aggregate *node, char ***environ_cp,
		char *terminal, t_session *sesh)
{
	int			dupret;
	struct stat	buf;
	int			open_fd;

	open_fd_if_needed(node->close_fd, terminal);
	if (is_nb(node->dest))
		open_fd = ft_atoi(node->dest);
	else if (node->close_fd == 1)
	{
		redir_to_file(node, sesh);
		return ;
	}
	if (fstat(open_fd, &buf) < 0)
	{
		ft_err_print(node->dest, NULL, "Bad file descriptor", 2);
		return ;
	}
	if (dup2(open_fd, node->close_fd) < 0)
	{
		ft_err_print(NULL, "dup2", "failed", 2);
		return ;
	}
	exec_tree(node->cmd, environ_cp, terminal, sesh);
}
