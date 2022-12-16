/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:21:00 by jniemine          #+#    #+#             */
/*   Updated: 2022/12/16 16:52:12 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_treenode	*init_cmd_node(char *cmd)
{
	t_treenode	*new;

	if (!cmd || !*cmd)
		return (NULL);
	new = ft_memalloc(sizeof(*new));
	new->type = CMD;
	((t_cmdnode *)new)->type = CMD;
	((t_cmdnode *)new)->cmd = make_arg_array(cmd);
	return (new);
}

t_treenode	*parse_left_cmd(t_token *tokens, int i_tok)
{
	t_treenode	*redir;
	int			cmd;

	redir = NULL;
	cmd = -1;
	if (i_tok >= 0 && tokens[i_tok].token == WORD)
		cmd = i_tok;
	while (i_tok >= 0 && tokens[i_tok].token != PIPE
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
	combine_words(&tokens[i_tok]);
	return (parse_redirections(tokens, i_tok, cmd));
}

t_treenode	*parse_right_cmd(t_token *tokens, int i_tok)
{
	t_treenode	*redir;
	t_treenode	*redir_start;
	int			start;
	int			cmd;

	combine_words(&tokens[i_tok]);
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

t_treenode	*build_tree(t_token *tokens)
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
