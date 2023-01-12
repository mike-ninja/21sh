/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_banner.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:31:02 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/12 17:08:34 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	banner_padding(size_t str_len)
{
	struct winsize	arg;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &arg) < 0)
	{
		ft_err_print(NULL, NULL, "could not get the terminal size", 2);
		exit(1);
	}
	return ((arg.ws_col - str_len) >> 1);
}

static void	jakke_and_mikey(void)
{
	int		padd;
	char	*str;

	str = "       __      __   __        ___     __  ____ __      ";
	padd = banner_padding(ft_strlen(str));
	ft_printf("\n%*s%s\n", padd, "", str);
	ft_printf("%*s%s\n", padd, "",
		"      / ____ _/ /__/ /_____  ( _ )   /  |/  (_/ /_____ ");
	ft_printf("%*s%s\n", padd, "",
		" __  / / __ `/ //_/ //_/ _ \\/ __ \\/|/ /|_/ / / //_/ _ \\");
	ft_printf("%*s%s\n", padd, "",
		"/ /_/ / /_/ / ,< / ,< /  __/ /_/  </ /  / / / ,< /  __/");
	ft_printf("%*s%s\n", padd, "",
		"\\____/\\__,_/_/|_/_/|_|\\___/\\____/\\/_/  /_/_/_/|_|\\___/");
	ft_printf("%*s%s\n", padd, "",
		"                                                       ");
}

static void	banner(void)
{
	int		padd;
	char	*str;

	str = "        _      _    _        _ _ ";
	padd = banner_padding(ft_strlen(str));
	ft_printf("%*s%s\n", padd, "", str);
	ft_printf("%*s%s\n", padd, "",
		"  _ __ (_)_ _ (_)__| |_  ___| | |");
	ft_printf("%*s%s\n", padd, "",
		" | '  \\| | ' \\| (_-< ' \\/ -_) | |");
	ft_printf("%*s%s\n\n", padd, "",
		" |_|_|_|_|_||_|_/__/_||_\\___|_|_|");
}

void	banner_print(void)
{
	ft_run_capability("cl");
	jakke_and_mikey();
	banner();
}
