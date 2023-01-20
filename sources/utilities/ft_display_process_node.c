/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_process_node.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:52:01 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/20 12:44:28 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	display_state(int status)
{
	if (status == 0)
		ft_printf("%2s%-24s", "", "Done");
	else if (status == 1)
		ft_printf("%2s%-24s", "", "Stopped");
	else if (status == 2)
		ft_printf("%2s%-24s", "", "Terminated");
	else
		ft_printf("%2s%-24s", "", "Running");
}

void	display_process_node(t_proc *node)
{
	ft_printf("[%d]", node->index);
	/* if (node->line = 0)
		ft_putchar('+');
	else if (node->line = 1)
		ft_putchar('-');
	else
		ft_putchar(' '); */
	ft_printf("%c", node->queue);
	display_state(node->status);
	ft_print_dbl_array(node->command);
	ft_printf("\n");
}
