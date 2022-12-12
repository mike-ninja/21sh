/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raw_enable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 08:41:48 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/12 15:10:29 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/**
 * It puts the terminal into raw mode
 *
 * @return The original terminal settings.
 */
struct termios	ft_raw_enable(void)
{
	struct termios	orig_termios;
	struct termios	raw;

	if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
	{
		write(2, "error tcgetattr\n", 16);
		exit(1);
	}
	raw = orig_termios;
	raw.c_lflag &= ~(ICANON | ECHO | IEXTEN);
	raw.c_iflag &= ~(IXON | BRKINT);
	raw.c_cc[VMIN] = 1;
	raw.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
	{
		write(2, "error tcsetattr\n", 16);
		exit(1);
	}
	return (orig_termios);
}
