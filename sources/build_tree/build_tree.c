/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:21:00 by jniemine          #+#    #+#             */
/*   Updated: 2022/11/23 20:57:03 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static	int foreseer_of_tokens(t_token *tokens, const char **marks, int end);

int	increment_whitespace(char **line)
{
	int	i;

	i = 0;
	while ((*line)[i] && is_ws((*line)[i]))
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

int	ft_calc_chr(char *line, char c)
{
	int	res;

	res = 0;
	while (*line)
	{
		if (*line == c)
			++res;
		++line;
	}
	return (res);
}

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
		*cmd = '\0';
		++i;
	}
//	null_terminate_strings(args);
	return (args);
}

t_treenode	*init_cmd_node(char *cmd)
{
	t_treenode	*new;

	new = ft_memalloc(sizeof(*new));
	new->type = CMD;
	((t_cmdnode *)new)->type = CMD;
	((t_cmdnode *)new)->cmd = make_arg_array(cmd);
	return (new);
}

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

void free_cmd_node(t_cmdnode *node)
{
	if (node)
	{
		while (node->cmd)
		{
			ft_memdel(node->cmd);
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

//TODO remember to fee pipe and tokens array also
static void error_tok(t_token *tokens, t_treenode *redir_head, char *msg, char *symbol)
{
	while (tokens->token)
	{
		free_token(&(*tokens));
		++tokens;
	}
	while (redir_head)
	{
		free_redir_node(&redir_head);
		++redir_head;
	}
	if (!symbol)
		ft_printf("21sh: %s\n", msg);
	else
		ft_printf("21sh: %s `%s'\n", msg, symbol);
}

/* Should actually never return 0 */
static int redir_type(char *value)
{
	char	*type;
	char	*tmp;

	type = ft_strchr(value, ">");
	tmp = ft_strchr(value, "<");
	if (type && tmp)
		if (tmp < type)
			type = tmp;
	if (!type && tmp)
		type = tmp;
	if (ft_strequ(type, "<<<"))
		return (RE_IN_TRI);
	else if (ft_strequ(type, "<<"))
		return (RE_IN_TWO);
	else if (ft_strequ(type, "<"))
		return (RE_IN_ONE);
	else if (ft_strequ(type, ">>"))
		return (RE_OUT_TWO);
	else if (ft_strequ(type, ">"))
		return (RE_OUT_ONE);
	return (0);
}

/* TODO does << and <<< have any meaning at this point or <<< at all*/
/* <<< does something >>> does not */
/* Does OUT need O_RDWR ?? */
static t_treenode *init_redir_wrap(char *filepath, char *cmd, int redir_type)
{
	int	close_fd;

	if (redir_type == RE_IN_ONE || redir_type == RE_IN_TWO || redir_type == RE_IN_TRI)
		close_fd = STDIN_FILENO;
	else
		close_fd = STDOUT_FILENO;
	if (redir_type == RE_IN_ONE)
		return (init_redir(filepath, cmd, close_fd, O_RDONLY));
	if (redir_type == RE_OUT_ONE)
		return (init_redir(filepath, cmd, close_fd, O_CREAT | O_TRUNC | O_RDWR));
	if (redir_type == RE_OUT_TWO)
		return (init_redir(filepath, cmd, close_fd, O_CREAT | O_APPEND | O_RDWR));
}

static t_treenode *if_redir(t_token *tokens, t_treenode **redir, int i_tok, int cmd)
{
	int	redir_t;

	if (tokens[i_tok].token == REDIR)
	{
		if (!tokens[i_tok + 1].token || tokens[i_tok + 1].token != WORD)
			error_tok(tokens, *redir, "syntax error near unexpected token", tokens[i_tok].value);
		redir_t = redir_type(tokens[i_tok].value);
		if (!*redir)
		{
			if (cmd < 0)
				*redir = init_redir_wrap(tokens[i_tok + 1].value, NULL, redir_t);
			else // HERE WE NEED TO CREATE COMMAND NODE
				*redir = init_redir_wrap(tokens[i_tok + 1].value, NULL, redir_t);
		}
		else
		{
			// HERE WE NEED TO ADD NEW REDIR AS CHILD TO PREVIOUS
		}

	}
}

/*	Starting from the pipe, so we parse backwards and take the
	first redir in and out */
//TODO first go backwards until prev pipe or i_tok == 0 or semicolon
//THEN build cmd until REDIR
//THEN build linked list of redirections
t_treenode *parse_left_cmd(t_token *tokens, int i_tok)
{
	t_treenode	*redir;
	int			close_fd;
	int			cmd;
	char		*direction;

	redir = NULL;
	cmd = -1;
	while (i_tok && tokens[i_tok].token != PIPE)
	{
		if (tokens[i_tok].token == WORD)
			cmd = i_tok;
		--i_tok;
	}
	if (tokens[i_tok].token == PIPE)
		++i_tok;
	while (tokens[i_tok].token && tokens[i_tok].token != PIPE)
	{
		if_redir() //Add params
		}
	}

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
