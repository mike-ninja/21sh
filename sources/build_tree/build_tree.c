/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:21:00 by jniemine          #+#    #+#             */
/*   Updated: 2022/12/14 16:03:41 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void print_tree(t_treenode *head, int depth);
t_treenode *parse_redirections(t_token *tokens, int i_tok, int cmd);

int increment_whitespace(char **line)
{
	int i;

	i = 0;
	while (*line && (*line)[i] && is_ws((*line)[i]))
		++i;
	*line += i;
	return (i);
}

int increment_not_whitespace(char **line)
{
	int i;

	i = 0;
	while ((*line)[i] && !is_ws((*line)[i]))
		++i;
	*line += i;
	return (i);
}

int ft_calc_chr(char *line, char c)
{
	int res;

	res = 0;
	while (line && *line)
	{
		if (*line == c)
			++res;
		++line;
	}
	return (res);
}

t_treenode *init_cmd_node(char *cmd)
{
	t_treenode *new;

	if (!cmd || !*cmd)
		return (NULL);
	new = ft_memalloc(sizeof(*new));
	new->type = CMD;
	((t_cmdnode *)new)->type = CMD;
	((t_cmdnode *)new)->cmd = make_arg_array(cmd);
	return (new);
}

void free_cmd_node(t_cmdnode *node)
{
	if (node)
	{
		while (node->cmd)
		{
			ft_memdel((void **)&node->cmd);
			++node->cmd;
		}
	}
}


void free_redir_node(t_redir **redir)
{
	free_cmd_node((t_cmdnode *)(*redir)->cmd);
	ft_memdel((void **)&(*redir)->filepath);
	*redir = NULL;
}

// TODO remember to fee pipe and tokens array also
void error_tok(t_token *tokens, t_treenode *redir_head, char *msg, char *symbol)
{
	//THIS FUNCTION SHOULD BE REFACTORED????
	if (!symbol)
		ft_printf("21sh: %s\n", msg);
	else
		ft_printf("21sh: %s `%s'\n", msg, symbol);
	while (tokens->token)
	{
		free_token(&(*tokens));
		++tokens;
	}
	while (redir_head)
	{
		free_redir_node(((t_redir **)&redir_head));
		++redir_head;
	}
}

char *get_file(char *value)
{
	int start;
	int end;
	char *res;

	start = 1;
	if (!value)
		return (NULL);
	if (value[start] == value[start - 1] || value[start] == '&')
		++start;
	while (value[start] && is_ws(value[start]))
		++start;
	end = start;
	while (value[end] && !is_ws(value[end]))
		++end;
	if (end <= start)
		return (NULL);
	res = ft_strsub(value, start, end - start);
	return (res);
}

t_treenode *init_aggregation_node(int close_fd, int open_fd, t_treenode *cmd)
{
	t_treenode *res;

	res = ft_memalloc(sizeof(*res));
	res->type = AGGREGATION;
	((t_aggregate *)res)->type = AGGREGATION;
	((t_aggregate *)res)->close_fd = close_fd;
	((t_aggregate *)res)->open_fd = open_fd;
	((t_aggregate *)res)->cmd = cmd;
	return (res);
}

int if_aggregation(t_token *tokens, t_treenode **redir, int i_tok, int cmd)
{
	char *dest;
	int close_fd;

	dest = get_file(ft_strchr(tokens[i_tok].value, '>'));
	if (!dest)
		dest = get_file(ft_strchr(tokens[i_tok].value, '<'));
	if (!dest)
	{
		error_tok(tokens, *redir, "syntax error near unexpected token", "newline");
		return (1);
	}
	close_fd = get_close_fd(tokens[i_tok].value);
	if (close_fd < 0)
		close_fd = 1;
	if (!*redir)
	{
		if (cmd < 0)
			*redir = init_aggregation_node(close_fd, ft_atoi(dest), NULL);
		else
			*redir = init_aggregation_node(close_fd, ft_atoi(dest), init_cmd_node(tokens[cmd].value));
	}
	else
	{
		if ((*redir)->type == REDIR)
			((t_redir *)(*redir))->cmd = init_aggregation_node(close_fd, ft_atoi(dest), (((t_redir *)(*redir))->cmd));
		if ((*redir)->type == CLOSEFD)
			((t_closefd *)(*redir))->cmd = init_aggregation_node(close_fd, ft_atoi(dest), (((t_closefd *)(*redir))->cmd));
		if ((*redir)->type == AGGREGATION)
			((t_aggregate *)(*redir))->cmd = init_aggregation_node(close_fd, ft_atoi(dest), (((t_aggregate *)(*redir))->cmd));
		traverse_node(redir);
	}
	ft_strdel(&dest);
	return (0);
}


/*	Starting from the pipe, so we parse backwards and take the
	first redir in and out */
t_treenode *parse_left_cmd(t_token *tokens, int i_tok)
{
	t_treenode *redir;
	int cmd;

	redir = NULL;
	cmd = -1;
	if (i_tok >= 0 && tokens[i_tok].token == WORD)
		cmd = i_tok;
	while (cmd < 0 && i_tok >= 0 && tokens[i_tok].token != PIPE
			&& tokens[i_tok].token != SEMICOLON)
	{
		if (tokens[i_tok].token == WORD)
			cmd = i_tok;
		--i_tok;
	}
	if (i_tok < 0)
		i_tok = 0;
	while (i_tok && tokens[i_tok].token != PIPE
			&& tokens[i_tok].token != SEMICOLON)
		--i_tok;
	if (tokens[i_tok].token == PIPE || tokens[i_tok].token == SEMICOLON)
		++i_tok;
	return (parse_redirections(tokens, i_tok, cmd));
}

t_treenode *parse_right_cmd(t_token *tokens, int i_tok)
{
	t_treenode *redir;
	t_treenode *redir_start;
	int start;
	int cmd;

	redir_start = redir;
	redir = NULL;
	cmd = -1;
	start = i_tok;
	while (cmd < 0 && tokens[i_tok].value && tokens[i_tok].token != PIPE
			&& tokens[i_tok].token != SEMICOLON)
	{
		if (tokens[i_tok].token == WORD)
			cmd = i_tok;
		++i_tok;
	}
	i_tok = start;
	return (parse_redirections(tokens, i_tok, cmd));
}

t_treenode *create_command_tree(t_token *tokens, int i_tok, int semicol)
{
	int			pipe;
	t_treenode	*head;

	if (tokens[i_tok].token == SEMICOLON)
		return (NULL);
	pipe = foreseer_of_tokens(tokens, PIPE, i_tok, semicol);
	if (pipe >= 0)
		head = create_pipe_node(tokens, pipe);
	else
		head = parse_right_cmd(tokens, i_tok);
	return (head);
}

t_treenode *init_semicolon(void)
{
	t_treenode *semicolon;

	semicolon = ft_memalloc(sizeof(*semicolon));
	semicolon->type = SEMICOLON;
	(((t_semicolon *)semicolon)->type) = SEMICOLON;
	(((t_semicolon *)semicolon)->left) = NULL;
	(((t_semicolon *)semicolon)->right) = NULL;
	return (semicolon);
}

t_treenode *create_semicolon_node(t_token *tokens, int i_tok, int end)
{
	t_treenode	*semicolon;
	int			next_semicol;

	if (!tokens[i_tok].token)
		return (NULL);
	semicolon = init_semicolon();
	next_semicol = foreseer_of_tokens(tokens, SEMICOLON, i_tok, end);
	if (next_semicol >= 0)
		(((t_semicolon *)semicolon)->right) = create_semicolon_node(tokens, next_semicol + 1, end);
	else
		next_semicol = end;
	(((t_semicolon *)semicolon)->left) = create_command_tree(tokens, i_tok, next_semicol);
	return (semicolon);
}

t_treenode *build_tree(t_token *tokens)
{
	t_treenode	*head;
	int			semicolon;
	int			pipe;

	head = NULL;
	if (!tokens)
		return (head);
	head = create_semicolon_node(tokens, 0, calculate_tokens(tokens));
	return (head);
}
