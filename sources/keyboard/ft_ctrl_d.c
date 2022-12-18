/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 20:26:30 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/18 20:56:01 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	display_input(t_term *t)
{
	char	**tmp;

	tmp = t->nl_addr + 1;
	while (*tmp)
	{
		if (!*(tmp + 2))
		{
			write(1, *tmp, ft_strlen(*tmp) - 1);
			break ;
		}
		else
			write(1, *tmp, *(tmp + 1) - *tmp);
		tmp++;
	}
}

int	ctrl_d(t_term *t)
{
	char	**tmp;

	if (!t->bytes)
		return (-1);
	if (t->index < t->bytes)
		ft_delete(t);
	if (t->heredoc && !*t->nl_addr[t->c_row])
	{
		ft_putstr("21sh: warning: here-document at line ");
		ft_putnbr(t->c_row);
		ft_putstr(" delimited by end-of-file (wanted `EOF')\n");
		display_input(t);
		ft_end_cycle(t);
		ft_restart_cycle(t);
		return (1);
	}
	return (0);
}
