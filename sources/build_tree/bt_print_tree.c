/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_print_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:22:15 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/06 22:42:37 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/* Just calculate left of node, because next one is printed below */
static int	calculate_nodes(t_treenode *head, int n)
{
	if (!head)
		return (n);
	if (head->type == SEMICOLON)
		n = calculate_nodes(((t_semicolon *)head)->left, ++n);
	else if (head->type == PIPE)
	{
		n = calculate_nodes(((t_pipenode *)head)->left, ++n);
		n = calculate_nodes(((t_pipenode *)head)->right, n);
	}
	else if (head->type == REDIR)
		n = calculate_nodes(((t_redir *)head)->cmd, ++n);
	else if (head->type == CLOSEFD)
		n = calculate_nodes(((t_closefd *)head)->cmd, ++n);
	else if (head->type == AGGREGATION)
		n = calculate_nodes(((t_aggregate *)head)->cmd, ++n);
	else if (head->type == LOGICAL_AND || head->type == LOGICAL_OR)
	{
		n = calculate_nodes(((t_logicalop *)head)->left, ++n);
		n = calculate_nodes(((t_logicalop *)head)->right, ++n);
	}
	else if (head->type == CMD)
		return (++n);
	return (n);
}

static void print_tab(int n)
{
	while (n--)
		ft_printf("    ");
}

//TODO make calculator for alignment
static void printer(t_treenode *head, int n)
{
	if (!head)
		return;
	if (head->type == SEMICOLON)
	{
		print_tab(n);
		ft_printf("%-11s\n", "SEMICOLON");
		print_tab(n);
		ft_printf("%-11s\n", "/");
		printer(((t_semicolon *)head)->left, --n);
	}
	else if (head->type == PIPE)
	{
		print_tab(n);
		ft_printf("%4s\n", "PIPE");
		print_tab(n);
		ft_printf("%-3s", "/");
		ft_printf("%s\n", "\\");
		print_tab(n - 1);
		printer(((t_pipenode *)head)->left, 0);
		print_tab(1);
		printer(((t_pipenode *)head)->right, 0);
		ft_printf("\n");
	}
	else if (head->type == REDIR)
		;
	else if (head->type == CLOSEFD)
		;
	else if (head->type == AGGREGATION)
		;
	else if (head->type == LOGICAL_AND || head->type == LOGICAL_OR)
	{
		;
	}
	else if (head->type == CMD)
		ft_printf("%s", *((t_cmdnode *)head)->cmd);
}

void print_tree(t_treenode *head)
{
	int n;

	n = calculate_nodes(head, 0);
	printer(head, n);
	ft_printf("N: %d\n", n);
	exit (0);
}
