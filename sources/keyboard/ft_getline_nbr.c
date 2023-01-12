/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getline_nbr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:39:35 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/12 11:28:02 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

extern t_term	*g_t;

/*
 * It gets the current line number of the cursor
 *
 * @return The line number of the cursor.
 */
int	ft_get_linenbr(void)
{
	char	buf[32];
	int		len;
	int		i;

	ft_memset(buf, '\0', sizeof(buf));
	write(0, "\033[6n", 4);
	read(0, buf, 32);
	len = ft_strlen(buf);
	ft_printf("len -> %d\n", len);
	ft_putstr_fd(buf, 1);
	while (len && buf[len] != ';')
		len--;
	ft_printf("col -> %d\n", ft_atoi(buf + len + 1));
	ft_printf("row -> %d\n", ft_atoi(buf + 2));
	i = 0;
	len = 0;
	while (buf[i] && buf[i] != ';')
	{
		if (ft_isdigit(buf[i]))
			buf[len++] = buf[i];
		i++;
	}
	ft_strclr(buf + len);
	return (ft_atoi(buf) - 1);
}
// int	ft_get_linenbr(void)
// {
// 	char	buf[32];
// 	int		len;
// 	int		i;

// 	ft_memset(buf, '\0', sizeof(buf));
// 	write(0, "\033[6n", 4);
// 	read(0, buf, 32);
// 	i = 0;
// 	len = 0;
// 	while (buf[i] && buf[i] != ';')
// 	{
// 		if (ft_isdigit(buf[i]))
// 			buf[len++] = buf[i];
// 		i++;
// 	}
// 	ft_strclr(buf + len);
// 	return (ft_atoi(buf) - 1);
// }

void	get_term_val(ssize_t *term_val)
{
	char	buf[32];
	int		len;

	ft_memset(buf, '\0', sizeof(buf));
	write(0, "\033[6n", 4);
	read(0, buf, 32);
	len = ft_strlen(buf);
	ft_putstr_fd(buf, 1);
	while (len && buf[len] != ';')
		len--;
	term_val[0] = ft_atoi(buf + len + 1) - 1;
	term_val[1] = ft_atoi(buf + 2) - 1;
}
