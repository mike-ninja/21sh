/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getline_nbr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:39:35 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/09 10:38:31 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It gets the current line number of the cursor
 *
 * @return The line number of the cursor.
 */
int	ft_get_linenbr(void)
{
	char	buf[2048];
	int		len;
	int		i;

	ft_memset(buf, '\0', sizeof(buf));
	write(0, "\x1b[6n", 4);
	len = 0;
	while (read(0, buf + len, 1) == 1)
	{
		if (buf[len++] == 'R' || len > 6)
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
