/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_create_semicolon_node.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:43:28 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/12 15:50:23 by jniemine         ###   ########.fr       */
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

t_treenode	*create_semicolon_node(t_token *tokens, int i_tok, int end)
{
	t_treenode	*semicolon;
	int			next_semicol;

	if (!tokens[i_tok].token)
		return (NULL);
	semicolon = init_semicolon();
	next_semicol = foreseer_of_tokens(tokens, SEMICOLON, i_tok, end);
	if (next_semicol >= 0)
		(((t_semicolon *)semicolon)->right) = create_semicolon_node(tokens,
				next_semicol + 1, end);
	else
		next_semicol = end;
	(((t_semicolon *)semicolon)->left) = create_logical_op_tree(tokens,
			i_tok, next_semicol);
	return (semicolon);
}
