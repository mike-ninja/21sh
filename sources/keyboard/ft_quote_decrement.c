/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_decrement.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:23:10 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/09 10:13:59 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	ft_quote_decrement(t_term *t, int num)
{
	if (!(t->q_qty % 2))
	{	
		t->quote = t->inp[t->index - num];
		t->q_qty--;
	}
	else if ((t->q_qty % 2) && t->quote == t->inp[t->index - num])
	{
		t->quote = 0;
		t->q_qty--;
	}
}
