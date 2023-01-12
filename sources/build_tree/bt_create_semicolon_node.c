/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_create_semicolon_node.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:43:28 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/13 00:21:20 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_treenode	*init_semicolon(void)
{
	t_treenode	*semicolon;

	semicolon = ft_memalloc(sizeof(*semicolon));
	semicolon->type = SEMICOLON;
	(((t_semicolon *)semicolon)->type) = SEMICOLON;
	(((t_semicolon *)semicolon)->left) = NULL;
	(((t_semicolon *)semicolon)->right) = NULL;
	return (semicolon);
}

int	next_semi_or_amp(t_tokens *tokens, int i_tok, int end)
{
	int			next_semicol;
	int			next_ampersand;

	next_semicol = foreseer_of_tokens(tokens, SEMICOLON, i_tok, end);
	next_ampersand = foreseer_of_tokens(tokens, AMPERSAND, i_tok, end);
	if (next_semicol < next_ampersand)
		return (next_semicol);
	return (next_ampersand);
}
/* <cmd>& buts it in the background, doing <samecmd>& again kills the old and stars a new */
/* Ampersand node should also have just right and left, right for next node left for cmd */
/* man kill -> SIGCONT, could be answer for vim ctrl+z problem */
t_treenode	*create_semicolon_node(t_token *tokens, int i_tok, int end)
{
	t_treenode	*semi_or_amp;
	int			next_semi_or_amp;

	if (!tokens[i_tok].token)
		return (NULL);
	semi_or_amp = init_semicolon();
	next_semi_or_amp = next_semicolon_or_ampersand(tokens, i_tok, end);
	if (next_semi_or_amp >= 0)
	{
//		if (tokens[next_semi_or_amp].token == SEMICOLON)
			(((t_semicolon *)semi_or_amp)->right) = create_semicolon_node(tokens,
				next_semi_or_amp + 1, end);
//		else if (tokens[next_semi_or_amp].token == AMPERSAND)
//			(((t_semicolon *)semi_or_amp)->right) = create_semicolon_node(tokens,
//				next_semi_or_amp + 1, end);
	}
	else
		next_semicol = end;
	(((t_semicolon *)semi_or_amp)->left) = create_logical_op_tree(tokens,
			i_tok, next_semicol);
	return (semi_or_amp);
}
