/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setcursor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 13:43:20 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/11 15:59:40 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * It sets the cursor to the given column and row
 * 
 * @param col The column number to move the cursor to.
 * @param row the row number of the cursor
 */
void	ft_setcursor(ssize_t col, ssize_t row)
{
	char	*cm;

	cm = tgetstr("cm", NULL);
	tputs(tgoto(cm, (int)col, (int)row), 1, ft_putc);
}
