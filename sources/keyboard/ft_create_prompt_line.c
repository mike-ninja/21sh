/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_prompt.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:40:40 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/11 21:06:13 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It creates a new line for the prompt
 *
 * @param t the term structure
 * @param loc the location of the cursor in the command line
 */
void	ft_create_prompt_line(t_term *t, ssize_t loc)
{
	int	row;

	row = ft_get_linenbr();
	t->c_row++;
	t->total_row++;
	if (t->start_row + t->total_row >= t->ws_row)
		ft_run_capability("sf");
	else
		row++;
	t->c_col = t->m_prompt_len;
	ft_setcursor(0, row);
	write(1, MINI_PROMPT, (size_t)t->m_prompt_len);
	ft_add_nl_last_row(t, loc);
}
