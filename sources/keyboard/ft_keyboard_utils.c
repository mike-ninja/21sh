/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyboard_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:21:09 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/02 20:42:22 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * It writes a single character to the standard output.
 *
 * @param c The character to print.
 *
 * @return The number of bytes written.
 */
int	ft_putc(int c)
{
	return ((int)write(1, &c, 1));
}

/**
 * It reads one character from the standard input and returns it
 *
 * @return The character that was read from the standard input.
 */
int	ft_get_input(void)
{
	int	c;

	c = 0;
	read(STDIN_FILENO, &c, 1);
	return (c);
}

/**
 * It sets the cursor to the given column and row
 *
 * @param col The column number to move the cursor to.
 * @param row The row number of the cursor.
 */
void	ft_setcursor(ssize_t col, ssize_t row)
{
	char	*cm;

	cm = tgetstr("cm", NULL);
	tputs(tgoto(cm, (int)col, (int)row), 1, ft_putc);
}

/**
 * It gets the current line number of the cursor
 *
 * @return The line number of the cursor.
 */
int	ft_get_linenbr(void)
{
	char	buf[16];
	int		len;
	int		i;

	ft_memset(buf, '\0', sizeof(buf));
	write(0, "\033[6n", 4);
	len = 0;
	while (read(0, buf + len, 1) == 1)
	{
		if (buf[len++] == 'R')
			break ;
	}
	len = 0;
	i = 0;
	while (buf[i] && buf[i] != ';')
	{
		if (ft_isdigit(buf[i]))
			buf[len++] = buf[i];
		i++;
	}
	buf[len] = '\0';
	return (ft_atoi(buf) - 1);
}
