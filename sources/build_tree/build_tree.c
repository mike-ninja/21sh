/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:21:00 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/13 19:00:11 by jniemine         ###   ########.fr       */
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
	int			cmd;

	cmd = -1;
	if (!tokens[i_tok].value)
		return (NULL);
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
	if (tokens[i_tok].token == PIPE || is_semicolon_or_ampersand(tokens[i_tok].token))
		++i_tok;
	combine_words(&tokens[i_tok]);
	return (parse_redirections(tokens, i_tok, cmd));
}

t_treenode	*parse_right_cmd(t_token *tokens, int i_tok)
{
	int			start;
	int			cmd;

	if (!tokens[i_tok].value)
		return (NULL);
	combine_words(&tokens[i_tok]);
	cmd = -1;
	start = i_tok;
	while (cmd < 0 && tokens[i_tok].value && tokens[i_tok].token != PIPE
		&& !is_logicalop(tokens[i_tok].token)
		&& !is_semicolon_or_ampersand(tokens[i_tok].token))
	{
		if (tokens[i_tok].token == WORD)
			cmd = i_tok;
		++i_tok;
	}
	i_tok = start;
	return (parse_redirections(tokens, i_tok, cmd));
}

/*
static void init_head(t_token *tokens, **head)
{
	int next_semi_or_amp;

	next_semi_or_amp = next_semicolon_or_ampersand(tokens, 0, calculate_tokens(0));
}
*/

t_treenode	*build_tree(t_token *tokens)
{
	t_treenode	*head;

	head = NULL;
	if (!tokens)
		return (head);
	head = create_semicolon_node(tokens, 0, calculate_tokens(tokens));
	print_tree(head);
	return (head);
}
