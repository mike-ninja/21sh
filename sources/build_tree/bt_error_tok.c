/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_error_tok.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:32:10 by jniemine          #+#    #+#             */
/*   Updated: 2022/12/14 16:35:15 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void free_cmd_node(t_cmdnode *node)
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

static void free_redir_node(t_redir **redir)
{
	free_cmd_node((t_cmdnode *)(*redir)->cmd);
	ft_memdel((void **)&(*redir)->filepath);
	*redir = NULL;
}

// TODO remember to fee pipe and tokens array also
int error_tok(t_token *tokens, t_treenode *redir_head, char *msg, char *symbol)
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
	return (1);
}
