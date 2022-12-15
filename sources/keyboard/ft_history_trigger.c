/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_trigger.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:59:10 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/15 13:15:57 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * It copies the current input into a buffer, pushes the current input into
 * the history ft_vector, and sets the current row to the history row
 * 
 * @param t the term structure
 */
static void	ft_history_push(t_term *t)
{
	if (t->history_row == -1)
	{
		t->input_cpy = ft_strsub(t->nl_addr[t->c_row], 0, \
		ft_strlen(t->nl_addr[t->c_row]));
		if (*t->history_buff)
		{
			ft_nl_removal(t);
			ft_vec_push(&t->v_history, t->history_buff);
			ft_memset((void *)t->history_buff, '\0', \
			ft_strlen(t->history_buff));
		}
		t->history_row = t->c_row;
	}
	t->c_row = t->history_row;
}

/**
 * It updates the current
 * input line with the history line
 * 
 * @param t the term structure
 * @param history the history string to be copied into the input line
 */
static void	ft_history_inp_update(t_term *t, char *history)
{
	if (history)
	{
		ft_memset((void *)t->nl_addr[t->c_row], '\0', \
		ft_strlen(t->nl_addr[t->c_row]));
		ft_memcpy(t->nl_addr[t->c_row], history, ft_strlen(history));
	}
	else
	{
		ft_memset((void *)t->nl_addr[t->c_row], '\0', \
		ft_strlen(t->nl_addr[t->c_row]));
		if (t->input_cpy)
			ft_memcpy(t->nl_addr[t->c_row], history, ft_strlen(history));
	}
}

/**
 * It clears the line from the cursor to the end of the screen
 * 
 * @param t the term structure
 * @param row the row number of the line to be cleared
 */
static void	ft_history_clear_line(t_term *t, ssize_t row)
{
	if (row > t->history_row)
	{
		ft_setcursor(0, ft_get_linenbr() - (row - t->history_row));
		while (row > t->history_row)
		{
			ft_remove_nl_addr(t, row);
			t->total_row--;
			row--;
		}
	}
	else
		ft_setcursor(0, ft_get_linenbr());
	ft_run_capability("cd");
}

/**
 * It takes the current input, pushes it to the history, then replaces
 * the current input with the history entry
 * 
 * @param t The terminal structure
 * @param his The history number to be retrieved.
 * 
 * @return the address of the first element of the array.
 */
void	ft_history_trigger(t_term *t, ssize_t his)
{
	ssize_t	row;
	char	*history;

	if (t->c_row != t->total_row)
		return ;
	row = t->c_row;
	ft_history_push(t);
	ft_run_capability("vi");
	history = (char *)ft_vec_get(&t->v_history, t->v_history.len - (size_t)his);
	ft_history_inp_update(t, history);
	ft_history_reset_nl(t, t->nl_addr[t->history_row]);
	ft_history_clear_line(t, row);
	ft_quote_flag_reset(t);
	ft_print_input(t, t->c_row, 1);
	if (!history)
	{
		t->history_row = -1;
		ft_strdel(&t->input_cpy);
	}
	ft_run_capability("ve");
}
