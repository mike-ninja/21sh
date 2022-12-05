/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raw_disable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 08:43:24 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/05 16:37:51 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/**
 * It disables raw mode by setting the terminal attributes to the original
 * terminal attributes
 *
 * @param orig_termios The original terminal attributes.
 */
void	ft_raw_disable(struct termios orig_termios)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}
