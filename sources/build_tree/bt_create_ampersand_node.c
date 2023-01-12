/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_create_ampersand_node.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 23:56:47 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/13 00:13:14 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static t_ampersand *init_ampersand_node(void)
{
	t_treenode *ampersand;

	ampersand = ft_memalloc(sizeof(t_treenode *));
	ampersand->type = AMPERSAND;
	ampersand->ampersand.type = AMPERSAND;
	ampersand->ampersand.cmd = NULL;
	return (ampersand);
}

t_treenode *create_ampersand_node(t_token *tokens, int i_tok, int end)
{
	t_treenode *ampersand;

	ampersand = init_ampersand_node();

}