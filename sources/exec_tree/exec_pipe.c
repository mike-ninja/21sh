/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:15:20 by jakken            #+#    #+#             */
/*   Updated: 2022/12/12 13:01:27 by jniemine         ###   ########.fr       */
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

/* If wait before second fork, then this works(It should not): ls -l > lol | cat lol
	If no wai then this does not work(It should): rm nosuchfile 2>&1 | cat -e */
void exec_pipe(t_pipenode *pipenode, char ***environ_cp, char *terminal, t_session *sesh)
{
	int	pipefd[2];

	if(pipe(pipefd)	< 0)
	{
		exe_cmd_err("pipe failed", "exec_pipe");
		return ;
	}
	if(fork_wrap() == 0){
	  close(1);
	  dup(pipefd[1]);
	  close(pipefd[0]);
	  close(pipefd[1]);
	  exec_tree(pipenode->left,	environ_cp, terminal, sesh);
	  exit (1);
	}
	if(fork_wrap() == 0){
	  close(0);
	  dup(pipefd[0]);
	  close(pipefd[0]);
	  close(pipefd[1]);
	  exec_tree(pipenode->right, environ_cp, terminal, sesh);
	  exit (1);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	wait(0);
	wait(0);
}
