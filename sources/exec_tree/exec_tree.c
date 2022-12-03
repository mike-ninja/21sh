/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:23:35 by jakken            #+#    #+#             */
/*   Updated: 2022/12/03 18:50:28 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	free_node(t_treenode *head)
{
		if (!head)
			return ;
		if (head->type == PIPE)
		{
			free_node(((t_pipenode *)head)->left);
			((t_pipenode *)head)->left = NULL;
			free_node(((t_pipenode *)head)->right);
			((t_pipenode *)head)->right = NULL;
		}
		else if (head->type == CMD)
			;//ft_freeda((void ***)&((t_cmdnode *)head)->cmd, calc_chptr(((t_cmdnode *)head)->cmd));
		else if (head->type == REDIR)
		{
			free_node(((t_redir *)head)->cmd);
			ft_memdel((void **)&(((t_redir *)head)->filepath));
		}
		else if (head->type == AGGREGATION)
			free_node(((t_aggregate *)head)->cmd);
		free(head);
}

void exec_tree(t_treenode *head, char ***environ_cp)
{
		if (head->type == PIPE)
			exec_pipe((t_pipenode *)head, environ_cp);
		else if (head->type == CMD)
			execute_bin(((t_cmdnode *)head)->cmd, environ_cp);
		else if (head->type == REDIR)
			exec_redir((t_redir *)head, environ_cp);
		else if (head->type == AGGREGATION)
			exec_aggregate((t_aggregate *)head, environ_cp);
	//	free_node(head);
	//	head = NULL;
}
