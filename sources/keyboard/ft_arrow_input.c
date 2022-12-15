/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrow_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:27:59 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/14 17:38:45 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It moves the cursor to the right
 *
 * @param t the term structure
 *
 * @return The address of the next line break.
 */
static void	ft_right(t_term *t)
{
	if (&t->inp[t->index] == &t->nl_addr[t->c_row + 1][-1] \
		&& ft_is_prompt_line(t, t->c_row + 1))
		return ;
	if (&t->inp[t->index] == &t->nl_addr[t->c_row + 1][-1])
	{
		t->c_col = -1;
		t->c_row++;
		ft_setcursor(++t->c_col, (ssize_t)ft_get_linenbr() + 1);
	}
	else
	{
		t->c_col++;
		ft_run_capability("nd");
	}
	t->index++;
}

/*
 * It moves the cursor to the left
 *
 * @param t the term structure
 *
 * @return the number of lines that the input string
 * 		occupies.
 */
static void	ft_left(t_term *t)
{
	if (&t->inp[t->index] == t->nl_addr[t->c_row] \
		&& ft_is_prompt_line(t, t->c_row))
		return ;
	if (&t->inp[t->index] == t->nl_addr[t->c_row])
	{
		t->c_col = 0;
		if (t->c_row == 1)
			t->c_col = t->prompt_len;
		else if (ft_is_prompt_line(t, t->c_row - 1))
			t->c_col = t->m_prompt_len;
		t->c_col += t->nl_addr[t->c_row] - t->nl_addr[t->c_row - 1];
		t->c_row--;
		ft_setcursor(--t->c_col, (ssize_t)ft_get_linenbr() - 1);
	}
	else
	{
		t->c_col--;
		ft_run_capability("le");
	}
	t->index--;
}

/*
 * It handles the arrow keys
 *
 * @param t the term structure
 */
void	ft_arrow_input(t_term *t)
{
	if (t->ch == ARROW_RGHT && t->index)
		ft_left(t);
	else if (t->ch == ARROW_LFT && t->index < t->bytes)
		ft_right(t);
	else if (t->ch == ARROW_UP && (size_t)t->his < t->v_history.len)
		ft_history_trigger(t, ++t->his);
	else if (t->ch == ARROW_DOWN && t->his > 0)
		ft_history_trigger(t, --t->his);
}
