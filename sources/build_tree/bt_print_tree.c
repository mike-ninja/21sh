/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_print_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:22:15 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/13 11:36:58 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	print_exec(t_treenode *node)
{
	size_t		len;
	t_cmdnode	*root;

	root = (t_cmdnode *)node;
	len = ft_arrlen(root->cmd);
	ft_printf("exec ");
	if (len > 2)
		ft_printf("[%s] [1]%s [2]%s [3]%s\n", root->cmd[0], \
		root->cmd[1], root->cmd[2], root->cmd[3]);
	else if (len == 2)
		ft_printf("[%s] %s\n", root->cmd[0], root->cmd[1]);
	else
		ft_printf("[%s]\n", root->cmd[0]);
}

static void	check_type(t_treenode *root)
{
	if (!root)
		return ;
	else if (root->type == CMD && root->type)
		print_exec(root);
	else if (root->type == PIPE)
		ft_printf("[|]");
	else if (root->type == REDIR && ((t_redir *)root)->cmd->type == CMD
		&& ((t_redir *)root)->close_fd == STDOUT_FILENO
		&& ((t_redir *)root)->rights & O_APPEND)
		ft_printf(">> [%d] [%s]\n",
			root->type, *(((t_cmdnode *)((t_redir *)root)->cmd)->cmd));
	else if (root->type == REDIR
		&& ((t_redir *)root)->close_fd == STDOUT_FILENO)
		ft_printf("> [%d]\n", root->type);
	else if (root->type == REDIR && ((t_redir *)root)->close_fd == STDIN_FILENO)
		ft_printf("> [%d]\n", root->type);
	else if (root->type == SEMICOLON)
		ft_printf("[;]");
	else if (root->type == AMPERSAND)
		ft_printf("[&]");
	else if (root->type == AGGREGATION)
		ft_printf(">& [%d] [%s]\n", root->type, ((t_aggregate *)root)->cmd);
	else if (root->type == LOGICAL_AND)
		ft_printf("[&&]");
	else if (root->type == LOGICAL_OR)
		ft_printf("[||]");
}

void	split_print_tree(t_treenode *root, int lvl)
{
	if (root->type == AGGREGATION)
		rec_print_tree(((t_aggregate *)root)->cmd, lvl);
	else if (root->type == LOGICAL_AND || root->type == LOGICAL_OR)
	{
		rec_print_tree(((t_logicalop *)root)->left, lvl);
		print_spaces(lvl);
		check_type(root);
		ft_printf("\n");
		rec_print_tree(((t_logicalop *)root)->right, lvl);
	}
	else if (root->type == SEMICOLON)
	{
		rec_print_tree(((t_semicolon *)root)->left, lvl);
		print_spaces(lvl);
		check_type(root);
		ft_printf("\n");
		rec_print_tree(((t_semicolon *)root)->right, lvl);
	}
	else if (root->type == AMPERSAND)
	{
		rec_print_tree(((t_ampersand *)root)->left, lvl);
		print_spaces(lvl);
		check_type(root);
		ft_printf("\n");
		rec_print_tree(((t_ampersand *)root)->right, lvl);
	}
	else
	{
		print_spaces(lvl);
		check_type(root);
	}
}

void	rec_print_tree(t_treenode *root, int lvl)
{
	if (root == NULL)
		return ;
	lvl += COUNT;
	if (root->type == PIPE)
	{
		rec_print_tree(((t_pipenode *)root)->left, lvl);
		print_spaces(lvl);
		check_type(root);
		ft_printf("\n");
		rec_print_tree(((t_pipenode *)root)->right, lvl);
	}
	else if (root->type == REDIR)
	{
		print_spaces(lvl);
		check_type(root);
		rec_print_tree(((t_redir *)root)->cmd, lvl);
	}
	split_print_tree(root, lvl);
}

void	print_tree(t_treenode *head)
{
	write(1, "\n------------------ TREE PRINT ------------------\n", 51);
	if (head)
		rec_print_tree(head, 0);
	write(1, "\n------------------ TREE PRINT ------------------\n\n", 52);
}
