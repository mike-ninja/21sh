/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:25:07 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/11 20:58:23 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * It sets the cursor position
 * to the position of the character at the current index
 * 
 * @param t the term structure
 */
static void	set_new_cur_pos(t_term *t)
{
	char *end;

	end = NULL;
	t->c_row = 0;
	while (t->nl_addr[t->c_row])
	{
		if (t->nl_addr[t->c_row + 1])
			end = t->nl_addr[t->c_row + 1] - 1;
		else
			end = &t->inp[t->bytes];
		if (&t->inp[t->index] >= t->nl_addr[t->c_row] && &t->inp[t->index] <= end)
			break ;
		t->c_row++;
	}
	t->c_col = ft_get_prompt_len(t, t->c_row);
	t->c_col += &t->inp[t->index] - t->nl_addr[t->c_row];
	ft_setcursor(t->c_col, t->c_row);
}

/*
 * It resets the cursor position and prints the trail of the input string
 *
 * @param t the term structure
 */
void	ft_window_size(t_term *t)
{
	struct winsize	size;

	ft_run_capability("vi");
	if (ioctl(0, TIOCGWINSZ, &size) < 0)
		ft_exit_no_mem(1);
	t->ws_col = size.ws_col;
	t->ws_row = size.ws_row;
	if (*t->inp)
	{
		ft_reset_nl_addr(t);
		ft_run_capability("cl");
		ft_print_input(t, 0, 0);
		set_new_cur_pos(t);
	}
	ft_run_capability("ve");
}
