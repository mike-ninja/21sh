/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_print_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:22:15 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/09 13:08:27 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"
#define COUNT 10

/*
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
		print_tab(n - 1);
		printer(((t_semicolon *)head)->left, --n);
	}
	else if (head->type == PIPE)
	{
		ft_printf("%4s\n", "PIPE");
		print_tab(n);
		ft_printf("%-3s", "/");
		ft_printf("%s\n", "\\");
		print_tab(n - 1);
		printer(((t_pipenode *)head)->left, n);
		print_tab(1);
		printer(((t_pipenode *)head)->right, n);
		ft_printf("\n");
	}
	else if (head->type == REDIR)
	{
		ft_printf("%s\n", "REDIR");
		print_tab(n + 1);
		ft_printf("%s\n", "|");
		print_tab(n + 1);
		printer(((t_redir *)head)->cmd, n);
	}
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
*/
/*
static void    print_exec(t_treenode *root)
{
    size_t    len;

    len = ft_arrlen((void **)root->arg);
    ft_printf("exec ");
    if (len > 2)
        ft_printf("[%s] [1]%s [2]%s [3]%s\n", root->arg[0], \
        root->arg[1], root->arg[2], root->arg[3]);
    else if (len == 2)
        ft_printf("[%s] %s\n", root->arg[0], root->arg[1]);
    else
        ft_printf("[%s]\n", root->arg[0]);
}

static void    check_type(t_treenode *root)
{
    if (root->type == CMD && root->type)
        print_exec(root);
    else if (root->type == PIPE)
        ft_printf("[|]");
    else if (root->type == REDIR && ((t_redir *)root)->cmd->type == CMD && ((t_redir *)root)->close_fd == STDOUT_FILENO && ((t_redir *)root)->rights & O_APPEND)
        ft_printf(">> [%d] [%s]\n", root->type, *(((t_cmdnode *)((t_redir *)root)->cmd)->cmd));
    else if (root->type == REDIR && ((t_redir *)root)->cmd->type == CMD && ((t_redir *)root)->close_fd == STDOUT_FILENO)
        ft_printf("> [%d] [%s]\n", root->type, *(((t_cmdnode *)((t_redir *)root)->cmd)->cmd));
    else if (root->type == REDIR && ((t_redir *)root)->cmd->type == CMD && ((t_redir *)root)->close_fd == STDIN_FILENO)
        ft_printf("> [%d] [%s]\n", root->type, *(((t_cmdnode *)((t_redir *)root)->cmd)->cmd));
//    else if (root->type == AMP)
//        ft_printf("[&]");
    else if (root->type == SEMICOLON)
        ft_printf("[;]");
    else if (root->type == AGGREGATION)
	{
        ft_printf(">& [%d] [%s]\n", root->type, root->);//
	}
}

void    rec_print_tree(t_treenode *root, int lvl)
{
    int    i;

    if (root == NULL)
        return ;
    lvl += COUNT;
    rec_print_tree(((t_semicolon *)root)->right, lvl);
    ft_printf("\n");
    i = COUNT;
    while (i++ < lvl)
        ft_printf(" ");
    check_type(root);
    rec_print_tree(((t_semicolon *)root)->left, lvl);
}

void    tree_print(t_treenode *root)
{
    write(1, "\n------------------ TREE PRINT ------------------\n", 51);
    if (root)
        rec_print_tree(root, 0);
    write(1, "\n------------------ TREE PRINT ------------------\n\n", 52);
}

void print_tree(t_treenode *head)
{
	int n;

	n = calculate_nodes(head, 0);
//	tree_print(head);
//	printer(head, n);
//	ft_printf("N: %d\n", n);
//	exit (0);
}
*/