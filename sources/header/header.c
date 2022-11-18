/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:31:02 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/18 16:17:10 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	header_padding(size_t str_len)
{
	struct winsize	arg;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &arg);
	return ((arg.ws_col - str_len) >> 1);
}

static void	super_pinoy_boy(void)
{
	int		padd;
	char	*str;

	str = "  ___                    ___ _               ___           ";
	padd = header_padd(ft_strlen(str));
	ft_printf("\n%*s%s\n", padd, "", str);
	ft_printf("%*s%s\n", padd, "",
		" / __|_  _ _ __  ___ _ _| _ (_)_ _  ___ _  _| _ ) ___ _  _ ");
	ft_printf("%*s%s\n", padd, "",
		" \\__ \\ || | '_ \\/ -_) '_|  _/ | ' \\/ _ \\ || | _ \\/ _ \\ || |");
	ft_printf("%*s%s\n", padd, "",
		" |___/\\_,_| .__/\\___|_| |_| |_|_||_\\___/\\_, |___/\\___/\\_, |");
	ft_printf("%*s%s\n", padd, "",
		"          |_|                           |__/          |__/ ");
}

static void	minishell_header(void)
{
	int		padd;
	char	*str;

	str = "        _      _    _        _ _ ";
	padd = header_padd(ft_strlen(str));
	ft_printf("%*s%s\n", padd, "", str);
	ft_printf("%*s%s\n", padd, "",
		"  _ __ (_)_ _ (_)__| |_  ___| | |");
	ft_printf("%*s%s\n", padd, "",
		" | '  \\| | ' \\| (_-< ' \\/ -_) | |");
	ft_printf("%*s%s\n\n", padd, "",
		" |_|_|_|_|_||_|_/__/_||_\\___|_|_|");
}

void	header_print(void)
{
	ft_run_capability("cl");
	super_pinoy_boy();
	minishell_header();
}
