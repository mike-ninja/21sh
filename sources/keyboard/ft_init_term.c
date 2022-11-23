/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_term.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:58:29 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/23 10:27:18 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

t_term	*g_t;

void	ft_init_term(t_term *t)
{
	ft_init_signals();
	t->ch = 0;
	ft_memset(t->inp, '\0', MAX_BUFF_SIZE);
	t->start_row = ft_get_linenbr();
	t->slash= 0;
	t->quote = 0;
	t->q_qty = 0;
	t->bytes = 0;
	t->c_row = 0;
	t->total_row = 0;
	t->ws_col = 0;
	t->ws_row = 0;
	t->index = 0;
	ft_history_get(t);
	g_t = t;
	t->nl_addr = NULL;
	ft_window_size(t);
	t->prompt_len = (ssize_t)ft_strlen(PROMPT);
	t->m_prompt_len = (ssize_t)ft_strlen(M_PROMPT);
	t->c_col = t->prompt_len;
	t->input_cpy = NULL;
	t->total_row_cpy = 0;
}
