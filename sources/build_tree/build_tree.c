/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:21:00 by jniemine          #+#    #+#             */
/*   Updated: 2022/11/22 20:28:47 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static	int foreseer_of_tokens(t_token *tokens, const char **marks, int end);

/* node can be either another redir or command, i guess */
t_treenode	*init_redir(char *filepath, t_treenode *cmd, int close_fd, int open_flags)
{
	t_treenode *redir;

	redir = ft_memalloc(sizeof(*redir));
	redir->type = REDIR;
	((t_redir *)redir)->type = REDIR;
	((t_redir *)redir)->cmd = cmd;
	((t_redir *)redir)->close_fd = close_fd;
	((t_redir *)redir)->filepath = filepath;
	((t_redir *)redir)->open_flags = open_flags;
	if (close_fd == 0)
		((t_redir *)redir)->rights = 0;
	else
		((t_redir *)redir)->rights = 0644;
	return (redir);
}

t_treenode *init_pipe(t_treenode *left,	t_treenode *right)
{
	t_treenode	*node;

//	if (left->type == CMD)
//		ft_printf("LEFT: %s\n",	*((t_cmdnode *)left)->cmd);
//	else if (left->type	== PIPE)
//		ft_printf("LEFT: PIPE\n");
//	if (right->type	== CMD)
//		ft_printf("rEIGHT: %s\n", *((t_cmdnode *)right)->cmd);
//	else if (right->type == PIPE)
//		ft_printf("RIGH: PIPE\n");
	node = ft_memalloc(sizeof(*node));
	node->type = PIPE;
	((t_pipenode *)node)->type = PIPE;
	((t_pipenode *)node)->left = left;
	((t_pipenode *)node)->right	= right;
	return (node);
}

/*	Starting from the pipe, so we parse backwards and take the
	first redir in and out */

//TODO first go backwards until prev pipe or i_tok == 0 or semicolon
//THEN build cmd until REDIR
//THEN build linked list of redirections
t_treenode *parse_left_cmd(t_token *tokens, int i_tok)
{
	int redir_in;
	int redir_out;

	redir_in = -1;
	redir_out = -1;
	while (i_tok--)
		if (tokens[i_tok].token == REDIR)
		{
			if (redir_in < 0 && ft_strchr(tokens[i_tok].value, '<'))
				redir_in = i_tok;
			else if (redir_out < 0)
				redir_out = i_tok;
		}
	if (redir_in >= 0)


}

t_treenode *create_pipe_node(t_tokens *tokens, int i_tok)
{
	t_treenode	*left;
	t_treenode	*right;
	char	*temp;

	if (tokens[i_tok] == PIPE)
	{
		// strsubs need	to be freed
		temp = ft_strsub(line, 0, *pipes - line	- 1);
		left = init_cmd_node(temp);
		line = *pipes +	1;
		if (*(pipes	+ 1))
			right =	create_pipe_node(++pipes, line);
		else
		{
			temp = ft_strsub(line, 0, ft_strlen(line));
			right =	init_cmd_node(temp);
		}
		return (init_pipe(left,	right));
	}
	return (NULL);
}

static 	int calculate_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].token)
		++i;
	return (i);
}

static	int foreseer_of_tokens(t_token *tokens, int mark, int start, int end)
{
	tokens = NULL;
	while (tokens[start].token && start < end)
	{
		if (tokens[start].token == mark)
			return (start);
		++start;
	}
	return (-1);
}

/* ls -l > file | head -n 5 > file < file2 | tail */
void	build_tree(t_token *tokens)
{
	const char *marks[] = {"PIPE", "REDIR", "SEMICOLON", "NEWLINE", NULL};
	int	i;
	int	pipe;

	i = 0;
	//First search for pipe
	//Everythin on left side of pipe goes to left (commands and redir nodes)
	//On right side goes the next pipe or if no pipe then command
	// Refactor the init pipe to use tokens, it should build the command on the left and on the right?
	pipe = foreseer_of_tokens(tokens, PIPE, 0, calculate_tokens(tokens));
	if (pipe >= 0)
		create_pipe_node(tokens, pipe);
}
