/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:21:00 by jniemine          #+#    #+#             */
/*   Updated: 2022/12/03 19:02:55 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

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

static char **make_arg_array(char *cmd)
{
	int argc;
	int i;
	char **args;

	increment_whitespace(&cmd);
	argc = ft_calc_chr(cmd, ' ') + 1;
	args = ft_memalloc(sizeof(*args) * (argc + 1));
	i = 0;
	while (*cmd && i < argc)
	{
		increment_whitespace(&cmd);
		args[i] = cmd;
		increment_not_whitespace(&cmd);
		if (*cmd)
		{
			*cmd = '\0';
			++cmd;
		}
		++i;
	}
	//	null_terminate_strings(args);
	return (args);
}

t_treenode *init_cmd_node(char *cmd)
{
	t_treenode *new;

	new = ft_memalloc(sizeof(*new));
	new->type = CMD;
	((t_cmdnode *)new)->type = CMD;
	((t_cmdnode *)new)->cmd = make_arg_array(cmd);
	return (new);
}

/* node can be either another redir or command, i guess */
t_treenode *init_redir(char *filepath, t_treenode *cmd, int close_fd, int open_flags)
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

t_treenode *init_pipe(t_treenode *left, t_treenode *right)
{
	t_treenode *node;

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
	((t_pipenode *)node)->right = right;
	return (node);
}

// TODO remember to fee pipe and tokens array also
static void error_tok(t_token *tokens, t_treenode *redir_head, char *msg, char *symbol)
{
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

/* Should actually never return 0 */
static int redir_type(char *value)
{
	char *type;
	char *tmp;

	type = ft_strchr(value, '>');
	tmp = ft_strchr(value, '<');
	if (type && tmp)
		if (tmp < type)
			type = tmp;
	if (!type && tmp)
		type = tmp;
	if (ft_strstr(type, "<<<"))
		return (RE_IN_TRI);
	else if (ft_strstr(type, "<<"))
		return (RE_IN_TWO);
	else if (ft_strstr(type, "<"))
		return (RE_IN_ONE);
	else if (ft_strstr(type, ">>"))
		return (RE_OUT_TWO);
	else if (ft_strstr(type, ">"))
		return (RE_OUT_ONE);
	return (0);
}

/* TODO does << and <<< have any meaning at this point or <<< at all*/
/* <<< does something >>> does not */
/* Does OUT need O_RDWR ?? */
static t_treenode *init_redir_wrap(char *filepath, t_treenode *cmd, int redir_type, int close_fd)
{
	if (close_fd < 0 && (redir_type == RE_IN_ONE || redir_type == RE_IN_TWO || redir_type == RE_IN_TRI))
		close_fd = STDIN_FILENO;
	else if (close_fd < 0)
		close_fd = STDOUT_FILENO;
	if (redir_type == RE_IN_ONE)
		return (init_redir(filepath, cmd, close_fd, O_RDONLY));
	else if (redir_type == RE_OUT_ONE)
		return (init_redir(filepath, cmd, close_fd, O_CREAT | O_TRUNC | O_RDWR));
	else if (redir_type == RE_OUT_TWO)
		return (init_redir(filepath, cmd, close_fd, O_CREAT | O_APPEND | O_RDWR));
	return (NULL);
}
/*
static char **make_arg_array(char *cmd)
{
	int	argc;
	int	i;
	char **args;

	increment_whitespace(&cmd);
	argc = ft_calc_chr(cmd, ' ') + 1;
	args = ft_memalloc(sizeof(*args) * (argc + 1));
	i = 0;
	while (*cmd && i < argc)
	{
		increment_whitespace(&cmd);
		args[i] = cmd;
		increment_not_whitespace(&cmd);
		++i;
	}
//	null_terminate_strings(args);
	return (args);
}
*/

/*
t_treenode	*init_cmd_node(char *cmd)
{
	t_treenode *new;

	new = ft_memalloc(sizeof(*new));
	new->type = CMD;
	((t_cmdnode *)new)->type = CMD;
	((t_cmdnode *)new)->cmd = make_arg_array(cmd);
	return (new);
}
*/

static char *get_file(char *value)
{
	int start;
	int end;
	char *res;

	start = 1;
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

static int get_close_fd(char *value)
{
	int digit;
	char *digits;
	int res;

	digit = 0;
	digits = NULL;
	while (ft_isdigit(value[digit]))
		++digit;
	if (digit > 0)
		digits = ft_strsub(value, 0, digit);
	if (digits)
	{
		res = ft_atoi(digits);
		ft_memdel((void **)&digits);
		return (res);
	}
	return (-1);
}

static int if_aggregation(t_token *tokens, t_treenode **redir, int i_tok, int cmd)
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
			*redir = init_aggregation_node(close_fd, atoi(dest), NULL);
		else // HERE WE NEED TO CREATE COMMAND NODE
			*redir = init_aggregation_node(close_fd, atoi(dest), init_cmd_node(tokens[cmd].value));
	}
	else
	{
		// HERE WE NEED TO ADD NEW REDIR AS CHILD TO PREVIOUS
		((t_redir *)(*redir))->cmd = init_aggregation_node(close_fd, atoi(dest), (((t_redir *)(*redir))->cmd));
	}
	return (0);
}

static int if_redir(t_token *tokens, t_treenode **redir, int i_tok, int cmd)
{
	int redir_t;
	char *dest;
	int close_fd;

	if (tokens[i_tok].token == AGGREGATION)
		return (if_aggregation(tokens, redir, i_tok, cmd));
	if (tokens[i_tok].token == REDIR)
	{
		close_fd = get_close_fd(tokens[i_tok].value);
		dest = get_file(ft_strchr(tokens[i_tok].value, '>'));
		if (!dest)
			dest = get_file(ft_strchr(tokens[i_tok].value, '<'));
		if (!dest)
		{
			error_tok(tokens, *redir, "syntax error near unexpected token", "newline");
			return (1);
		}
		redir_t = redir_type(tokens[i_tok].value);
		if (!*redir)
		{
			if (cmd < 0)
				*redir = init_redir_wrap(dest, NULL, redir_t, close_fd);
			else // HERE WE NEED TO CREATE COMMAND NODE
				*redir = init_redir_wrap(dest, init_cmd_node(tokens[cmd].value), redir_t, close_fd);
		}
		else
		{
			// HERE WE NEED TO ADD NEW REDIR AS CHILD TO PREVIOUS
			((t_redir *)(*redir))->cmd = init_redir_wrap(dest, (((t_redir *)(*redir))->cmd), redir_t, close_fd);
		}
	}
	return (0);
}

/*	Starting from the pipe, so we parse backwards and take the
	first redir in and out */
// TODO first go backwards until prev pipe or i_tok == 0 or semicolon
// THEN build cmd until REDIR
// THEN build linked list of redirections
static t_treenode *parse_left_cmd(t_token *tokens, int i_tok)
{
	t_treenode *redir;
	//	int			close_fd;
	int cmd;
	//	char		*direction;

	redir = NULL;
	cmd = -1;
	if (i_tok >= 0 && tokens[i_tok].token == WORD)
		cmd = i_tok;
	while (cmd < 0 && i_tok && tokens[i_tok].token != PIPE)
	{
		if (tokens[i_tok].token == WORD)
			cmd = i_tok;
		--i_tok;
	}
	if (tokens[i_tok].token == PIPE)
		++i_tok;
	while (tokens[i_tok].token && tokens[i_tok].token != PIPE)
	{
		if (if_redir(tokens, &redir, i_tok, cmd))
			return (NULL);
		++i_tok;
	}
	if (redir)
		return (redir);
	return (init_cmd_node(tokens[cmd].value));
}

static t_treenode *parse_right_cmd(t_token *tokens, int i_tok)
{
	t_treenode *redir;
	int start;
	//	int			close_fd;
	int cmd;
	//	char		*direction;

	redir = NULL;
	cmd = -1;
	start = i_tok;
	while (cmd < 0 && tokens[i_tok].value && tokens[i_tok].token != PIPE)
	{
		if (tokens[i_tok].token == WORD /*|| (i_tok > 0 && tokens[i_tok].token == WORD && tokens[i_tok - 1].token != REDIR)*/)
			cmd = i_tok;
		++i_tok;
	}
	i_tok = start;
	while (tokens[i_tok].token && tokens[i_tok].token != PIPE)
	{
		if (if_redir(tokens, &redir, i_tok, cmd))
			return (NULL);
		++i_tok;
	}
	if (redir)
		return (redir);
	return (init_cmd_node(tokens[cmd].value));
}

static int calculate_tokens(t_token *tokens)
{
	int i;

	i = 0;
	while (tokens[i].token)
		++i;
	return (i);
}

static int foreseer_of_tokens(t_token *tokens, int mark, int start, int end)
{
	if (!tokens)
		return (-1);
	while (tokens[start].token && start < end)
	{
		if (tokens[start].token == mark)
			return (start);
		++start;
	}
	return (-1);
}

t_treenode *create_pipe_node(t_token *tokens, int i_tok)
{
	t_treenode *left;
	t_treenode *right;
	int next_pipe;
	// char	*temp;

	left = NULL;
	right = NULL;
	if (tokens[i_tok].token == PIPE)
	{
		left = parse_left_cmd(tokens, i_tok - 1);
		if (!left)
			return (NULL);
		next_pipe = foreseer_of_tokens(tokens, PIPE, i_tok + 1, calculate_tokens(tokens));
		if (next_pipe >= 0)
			right = create_pipe_node(tokens, next_pipe);
		else
			right = parse_right_cmd(tokens, i_tok + 1);
		// strsubs need	to be freed
		//	temp = ft_strsub(line, 0, *pipes - line	- 1);
		//	left = init_cmd_node(temp);
		//	line = *pipes +	1;
		//	if (*(pipes	+ 1))
		//		right =	create_pipe_node(++pipes, line);
		//	else
		//	{
		//		temp = ft_strsub(line, 0, ft_strlen(line));
		//		right =	init_cmd_node(temp);
		//	}
		return (init_pipe(left, right));
	}
	return (NULL);
}

void print_array_as_line(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		ft_printf("%s ", arr[i]);
		++i;
	}
	ft_printf("\n");
}

void print_node(t_treenode *node)
{
	if (!node)
	{
		ft_printf("NULL\n");
		return;
	}
	else if (node->type == PIPE)
		ft_printf("Type: PIPE\n");
	else if (node->type == CMD)
	{
		ft_printf("Type: CMD Value: ");
		print_array_as_line(((t_cmdnode *)node)->cmd);
	}
	else if (node->type == REDIR)
		ft_printf("Type: REDIR\n");
}

void print_tree(t_treenode *head, int depth)
{
	int depth_temp;

	depth_temp = depth;
	if (!head)
		return;
	if (head->type == PIPE)
	{
		print_tree(((t_pipenode *)head)->right, depth + 1);
		ft_printf("\\");
		print_tree(((t_pipenode *)head)->left, depth + 1);
		ft_printf("/");
	}
	while (depth--)
		ft_printf("\t");
	print_node(head);
	while (depth_temp--)
		ft_printf("\t");
}

/* ls -l > file | head -n 5 > file < file2 | tail */
t_treenode *build_tree(t_token *tokens)
{
	//	const char *marks[] = {"PIPE", "REDIR", "SEMICOLON", "NEWLINE", NULL};
	//	int	i;
	t_treenode *head;
	int pipe;

	head = NULL;
	if (!tokens)
		return (head);
	//	i = 0;
	// First search for pipe
	// Everythin on left side of pipe goes to left (commands and redir nodes)
	// On right side goes the next pipe or if no pipe then command
	// Refactor the init pipe to use tokens, it should build the command on the left and on the right?
	pipe = foreseer_of_tokens(tokens, PIPE, 0, calculate_tokens(tokens));
	if (pipe >= 0)
		head = create_pipe_node(tokens, pipe);
	else
		head = parse_right_cmd(tokens, 0);
//	free_tokens(tokens);
	return (head);
}
