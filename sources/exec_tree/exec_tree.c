/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:23:35 by jakken            #+#    #+#             */
/*   Updated: 2022/12/13 12:19:01 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	free_node(t_treenode *head)
{
	if (!head)
		return ;
	if (head->type == SEMICOLON)
	{
		free_node(((t_semicolon *)head)->left);
		((t_semicolon *)head)->left = NULL;
		free_node(((t_semicolon *)head)->right);
		((t_semicolon *)head)->right = NULL;
	}
	if (head->type == PIPE)
	{
		free_node(((t_pipenode *)head)->left);
		((t_pipenode *)head)->left = NULL;
		free_node(((t_pipenode *)head)->right);
		((t_pipenode *)head)->right = NULL;
	}
	else if (head->type == CMD)
	{
		ft_freeda((void ***)&((t_cmdnode *)head)->cmd, calc_chptr(((t_cmdnode *)head)->cmd));
	}
	else if (head->type == REDIR)
	{
		free_node(((t_redir *)head)->cmd);
		ft_memdel((void **)&(((t_redir *)head)->filepath));
	}
	else if (head->type == CLOSEFD)
		free_node(((t_redir *)head)->cmd);
	else if (head->type == AGGREGATION)
		free_node(((t_aggregate *)head)->cmd);
	ft_memdel((void **)&head);
		// free(head);
}

void exec_tree(t_treenode *head, char ***environ_cp, char *terminal, t_session *sesh)
{
	//	ft_putstr_fd("TREE\n", 2);
		if (!head)
			return ;
//		ft_putstr_fd("TREE2\n", 2);
		if (head->type == SEMICOLON)
		{
		//	reset_fd(terminal);
			exec_tree((((t_semicolon *)head)->left), environ_cp, terminal, sesh);
			reset_fd(terminal);
			exec_tree((((t_semicolon *)head)->right), environ_cp, terminal, sesh);
		}
		else if (head->type == PIPE)
			exec_pipe((t_pipenode *)head, environ_cp, terminal, sesh);
		else if (head->type == CMD)
			execute_bin(((t_cmdnode *)head)->cmd, environ_cp, sesh);
		else if (head->type == REDIR)
			exec_redir((t_redir *)head, environ_cp, terminal, sesh);
		else if (head->type == AGGREGATION)
			exec_aggregate((t_aggregate *)head, environ_cp, terminal, sesh);
		else if (head->type == CLOSEFD)
			exec_closefd((t_closefd *)head, environ_cp, terminal, sesh);
	//	free_node(head);
	//	head = NULL;
}
