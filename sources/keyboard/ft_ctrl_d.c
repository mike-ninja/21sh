/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 20:26:30 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/19 15:56:24 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

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
		ft_putstr(" delimited by end-of-file (wanted `EOF')");
		ft_end_cycle(t);
		return (1);
	}
	return (0);
}
