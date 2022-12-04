/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_trigger.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:59:10 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/04 19:13:33 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It moves the cursor to the end of the line
 *
 * @param t the term structure
 */
static void	ft_history_trigger_end(t_term *t)
{
	t->index = t->bytes;
	t->c_row = t->total_row;
	if (ft_is_prompt_line(t, t->c_row))
	{
		if (!t->c_row)
			t->c_col = t->prompt_len;
		else
			t->c_col = t->m_prompt_len;
	}
	t->c_col += &t->inp[t->bytes] - t->nl_addr[t->c_row];
	ft_setcursor(t->c_col, t->total_row + t->start_row);
	ft_run_capability("ve");
}

/*
 * It sets the cursor to the beginning of the line, clears the screen, and
 * prints the prompt
 *
 * @param t the term structure
 */
static void	ft_history_trigger_start(t_term *t)
{
	ft_run_capability("vi");
	t->quote = 0;
	t->q_qty = 0;
	t->c_col = 0;
	t->c_row = 0;
	t->index = 0;
	t->total_row = 0;
	ft_setcursor(t->c_col, t->start_row);
	ft_run_capability("cd");
	ft_putstr(PROMPT);
}

/*
 * It takes a history number,
 * and if it exists, it copies it into the input buffer, otherwise it copies the
 * original input buffer
 *
 * @param t the term structure
 * @param his the history number to trigger
 */
void	ft_history_trigger(t_term *t, ssize_t his)
{
	char	*history;

	ft_history_trigger_start(t);
	history = (char *)ft_vec_get(&t->v_history, t->v_history.len - (size_t)his);
	if (history)
	{
		t->bytes = (ssize_t)ft_strlen(history);
		if (!t->input_cpy)
			t->input_cpy = ft_strdup(t->inp);
		ft_memset((void *)t->inp, '\0', BUFF_SIZE);
		ft_memcpy((void *)t->inp, (void *)history, (size_t)t->bytes);
	}
	else
	{
		t->bytes = (ssize_t)ft_strlen(t->input_cpy);
		ft_memset((void *)t->inp, '\0', BUFF_SIZE);
		ft_memcpy((void *)t->inp, (void *)t->input_cpy, (size_t)t->bytes);
		ft_strdel(&t->input_cpy);
	}
	ft_reset_nl_addr(t);
	ft_print_trail(t);
	ft_history_trigger_end(t);
}
