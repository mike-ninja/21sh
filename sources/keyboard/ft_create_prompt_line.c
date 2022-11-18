/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_prompt_line.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:40:40 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/18 16:12:01 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

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
	write(1, M_PROMPT, (size_t)t->m_prompt_len);
	ft_add_nl_last_row(t, loc);
}
