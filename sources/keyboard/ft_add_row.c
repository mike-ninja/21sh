/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_row.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:11:14 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/21 12:25:33 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * It adds a newline address to the array of newline addresses
 * 
 * @param t the term structure
 * @param pos the position of the newline character in the input string
 */
void	ft_add_nl_last_row(t_term *t, ssize_t pos)
{
	int		i;
	char	**new_arr;

	i = -1;
	new_arr = NULL;
	if (!t->nl_addr)
	{
		t->nl_addr = (char **)ft_memalloc(sizeof(char *) * 2);
		t->nl_addr[++i] = &t->inp[pos];
		t->nl_addr[++i] = NULL;
	}
	else
	{
		new_arr = (char **)ft_memalloc(sizeof(char *) * (size_t)(t->total_row + 2));
		while (t->nl_addr[++i])
			new_arr[i] = t->nl_addr[i];
		new_arr[i++] = &t->inp[pos];
		new_arr[i] = NULL;
		ft_memdel((void **)&t->nl_addr);
		t->nl_addr = new_arr;
	}
}

/**
 * It adds a new line in the middle of the array of new line addresses
 * 
 * @param t the term structure
 * @param row The row number where the newline is to be added.
 * @param pos the position of the newline character in the input string
 */
void	ft_add_nl_mid_row(t_term *t, ssize_t row, ssize_t pos)
{
	int		i;
	int		j;
	char	**new_arr;

	j = 0;
	i = -1;
	new_arr = (char **)ft_memalloc(sizeof(char *) * (size_t)(t->total_row + 2));
	while (++i <= t->total_row)
	{
		if (i == row)
			new_arr[i] = &t->inp[pos];
		else
			new_arr[i] = t->nl_addr[j++];
	}
	new_arr[i] = NULL;
	ft_memdel((void **)&t->nl_addr);
	t->nl_addr = new_arr;
}

/**
 * It sets the prompt
 * 
 * @param t the term structure
 * @param loc the location of the cursor in the command line
 */
void	ft_print_prompt(t_term *t, ssize_t loc)
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
