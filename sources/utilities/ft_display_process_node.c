/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_process_node.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:52:01 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/17 17:52:23 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	display_state(int status)
{
	if (status == RUNNING)
		ft_printf("%2s%-24s", "", "Running");
	else if (status == SUSPENDED)
		ft_printf("%2s%-24s", "", "Stopped");
	else if (status == EXITED)
		ft_printf("%2s%-24s", "", "Done");

}

void	display_process_node(t_proc *node)
{
	ft_printf("[%d]", node->index);
	ft_printf("%c", node->job);
	display_state(node->status);
	ft_print_dbl_array(node->command);
	ft_printf("\n");
}
