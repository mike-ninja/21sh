/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reset_nl_addr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:20:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/11 15:28:40 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	ft_reset_nl_addr(t_term *t)
{
	ssize_t	i;
	ssize_t	len;

	i = 0;
	len = 0;
	t->total_row = 0;
	if (t->nl_addr)
		ft_memdel((void **)&t->nl_addr);
	ft_add_nl_last_row(t, i);
	while (t->inp[++i])
	{
		len++;
		if (((len + ft_get_prompt_len(t, t->total_row)) + 1)
			/ (t->ws_col) || t->inp[i] == '\n')
		{
			ft_add_nl_last_row(t, i + 1);
			t->total_row++;
			len = -1;
		}
		if (t->inp[i] == D_QUO || t->inp[i] == S_QUO)
			ft_quote_handling(t, t->inp[i]);
	}
}
