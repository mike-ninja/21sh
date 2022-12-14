/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_if_aggregation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:18:53 by jniemine          #+#    #+#             */
/*   Updated: 2022/12/14 16:29:35 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_treenode	*init_aggregation_node(int close_fd, int open_fd, t_treenode *cmd)
{
	t_treenode	*res;

	res = ft_memalloc(sizeof(*res));
	res->type = AGGREGATION;
	((t_aggregate *)res)->type = AGGREGATION;
	((t_aggregate *)res)->close_fd = close_fd;
	((t_aggregate *)res)->open_fd = open_fd;
	((t_aggregate *)res)->cmd = cmd;
	return (res);
}

static void	make_child_for_prev(t_treenode **redir,
		char *dest, int close_fd)
{
	if ((*redir)->type == REDIR)
		((t_redir *)(*redir))->cmd = init_aggregation_node(close_fd,
				ft_atoi(dest), (((t_redir *)(*redir))->cmd));
	if ((*redir)->type == CLOSEFD)
		((t_closefd *)(*redir))->cmd = init_aggregation_node(close_fd,
				ft_atoi(dest), (((t_closefd *)(*redir))->cmd));
	if ((*redir)->type == AGGREGATION)
		((t_aggregate *)(*redir))->cmd = init_aggregation_node(close_fd,
				ft_atoi(dest), (((t_aggregate *)(*redir))->cmd));
	traverse_node(redir);
}

int	if_aggregation(t_token *tokens, t_treenode **redir, int i_tok, int cmd)
{
	char	*dest;
	int		close_fd;

	dest = get_file(ft_strchr(tokens[i_tok].value, '>'));
	if (!dest)
		dest = get_file(ft_strchr(tokens[i_tok].value, '<'));
	if (!dest)
		return (error_tok(tokens, *redir,
				"syntax error near unexpected token", "newline"));
	close_fd = get_close_fd(tokens[i_tok].value);
	if (close_fd < 0)
		close_fd = 1;
	if (!*redir)
	{
		if (cmd < 0)
			*redir = init_aggregation_node(close_fd, ft_atoi(dest), NULL);
		else
			*redir = init_aggregation_node(close_fd,
					ft_atoi(dest), init_cmd_node(tokens[cmd].value));
	}
	else
		make_child_for_prev(redir, dest, close_fd);
	ft_strdel(&dest);
	return (0);
}
