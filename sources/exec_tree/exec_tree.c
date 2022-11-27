/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:23:35 by jakken            #+#    #+#             */
/*   Updated: 2022/11/27 23:04:25 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void exec_tree(t_treenode *head, char ***environ_cp)
{
		if (head->type == PIPE)
			exec_pipe((t_pipenode *)head, environ_cp);
		else if (head->type == CMD)
			execute_bin(((t_cmdnode *)head)->cmd, environ_cp);
		else if (head->type == REDIR)
			exec_redir((t_redir *)head, environ_cp);
}
