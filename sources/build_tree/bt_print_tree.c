/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_print_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:48:35 by jniemine          #+#    #+#             */
/*   Updated: 2022/12/14 15:50:05 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void print_array_as_line(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		ft_printf("%s ", arr[i]);
		++i;
	}
	ft_printf("\n");
}

void print_node(t_treenode *node)
{
	if (!node)
	{
		ft_printf("NULL\n");
		return;
	}
	else if (node->type == PIPE)
		ft_printf("Type: PIPE\n");
	else if (node->type == SEMICOLON)
		ft_printf("Type: SEMICOLON\n");
	else if (node->type == CMD)
	{
		ft_printf("Type: CMD Value: ");
		print_array_as_line(((t_cmdnode *)node)->cmd);
	}
	else if (node->type == REDIR)
		ft_printf("Type: REDIR\n");
	else if (node->type == CLOSEFD)
		ft_printf("Type: CLOSEFD\n");
	else if (node->type == AGGREGATION)
		ft_printf("Type: AGGREGATION\n");
}

void print_tree(t_treenode *head, int depth)
{
	int depth_temp;

	depth_temp = depth;
	if (!head)
		return;
	if (head->type == PIPE)
	{
		ft_printf("PIPE RIGHT:\n");
		print_tree(((t_pipenode *)head)->right, depth + 1);
		ft_printf("PIPE LEFT:\n");
		print_tree(((t_pipenode *)head)->left, depth + 1);
	}
	if (head->type == SEMICOLON)
	{
		ft_printf("SEMI LEFT:\n");
		print_tree(((t_semicolon *)head)->left, depth + 1);
		ft_printf("SEMI RIGHT:\n");
		print_tree(((t_semicolon *)head)->right, depth + 1);
	}
	if (head->type == REDIR)
		print_tree(((t_redir *)head)->cmd, depth + 1);
	if (head->type == CLOSEFD)
		print_tree(((t_closefd *)head)->cmd, depth + 1);
	if (head->type == AGGREGATION)
		print_tree(((t_aggregate *)head)->cmd, depth + 1);
	print_node(head);
}
