/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:15:20 by jakken            #+#    #+#             */
/*   Updated: 2022/12/02 18:12:38 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	error_exit(char *msg)
{
	ft_putstr_fd("ERROR: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	exit(-1);
}

int	fork_wrap(void)
{
	int pid;

	pid = fork();
	if(pid == -1)
		error_exit("fork failed\n");
	return (pid);
}

void exec_pipe(t_pipenode *pipenode, char ***environ_cp)
{
	int	pipefd[2];
	int	waitstatus;

//	if (pipenode->left->type == CMD)
//	{
//		ft_putstr_fd("left:	", 2);
//		ft_putstr_fd(*((t_cmdnode *)pipenode->left)->cmd, 2);
//		ft_putstr_fd("\n", 2);
//	}
//	if (pipenode->right->type == CMD)
//	{
//		ft_putstr_fd("right: ", 2);
//		ft_putstr_fd(*((t_cmdnode *)pipenode->right)->cmd, 2);
//		ft_putstr_fd("\n", 2);
//	}
//	else if (pipenode->right->type == PIPE)
//	{
//		ft_putstr_fd("INPIPE left: ", 2);
//		if (((t_pipenode *)pipenode->left)->type == CMD)
//			ft_putstr_fd(*((t_cmdnode *)pipenode->left)->cmd, 2);
//		ft_putstr_fd("\n", 2);
//		ft_putstr_fd("INPIPE right:	", 2);
//		if (((t_pipenode *)pipenode->right)->type == CMD)
//			ft_putstr_fd(*((t_cmdnode *)pipenode->right)->cmd, 2);
//		else if (((t_pipenode *)pipenode->right)->type == PIPE)
//		{
//			ft_putstr_fd("PIPE", 2);
//			ft_putstr_fd("\n", 2);
//			ft_putstr_fd("CHILDREN LEFT	RIGHT: ", 2);
//			ft_putstr_fd(*((t_cmdnode *)((t_pipenode *)pipenode->right)->left)->cmd, 2);
//			ft_putstr_fd("		", 2);
//			ft_printf("ADDRESS:	%p", ((t_pipenode *)pipenode->right)->right);
//			ft_printf("ADDRESS:	%p", ((t_pipenode *)pipenode->right)->left);
//			ft_putstr_fd(ft_itoa(((t_cmdnode *)((t_pipenode	*)pipenode->right)->right)->type), 2);
//		//	ft_putstr_fd(*((t_cmdnode *)((t_pipenode *)pipenode->right)->right)->cmd, 2);
//		}
//		ft_putstr_fd("\n", 2);
//	}
//	ft_putstr_fd("-------------\n",	2);
	if(pipe(pipefd)	< 0	&& ft_printf("21sh:	pipe failed\n"))
		return ;
	if(fork_wrap() == 0){
	  close(1);
	  dup(pipefd[1]);
	  close(pipefd[0]);
	  close(pipefd[1]);
	  exec_tree(pipenode->left,	environ_cp);
	  exit (1);
	}
	if(fork_wrap() == 0){
	  close(0);
	  dup(pipefd[0]);
	  close(pipefd[0]);
	  close(pipefd[1]);
	  exec_tree(pipenode->right, environ_cp);
	  exit (1);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	wait(&waitstatus);
	wait(&waitstatus);
}
