/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_process_order.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 21:43:21 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/11 21:51:18 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	update_process_order(t_proc *head, int mode)
{
	/*
	Do something
	*/
	if (mode == 0)
	{
		while (head)
		{
			if (head->next && !head->next->next)
				head->job = '-';
			else if (!head->next)
				head->job = '+';
			else
				head->job = ' ';
			head = head->next;
		}
	}
}
