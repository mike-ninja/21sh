/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_banner.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:31:02 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/19 12:29:22 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	banner_padding(size_t str_len)
{
	struct winsize	arg;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &arg);
	return ((arg.ws_col - str_len) >> 1);
}

// static void	super_pinoy_boy(void)
// {
// 	int		padd;
// 	char	*str;

// 	str = "  ___                    ___ _               ___           ";
// 	padd = banner_padding(ft_strlen(str));
// 	ft_printf("\n%*s%s\n", padd, "", str);
// 	ft_printf("%*s%s\n", padd, "",
// 		" / __|_  _ _ __  ___ _ _| _ (_)_ _  ___ _  _| _ ) ___ _  _ ");
// 	ft_printf("%*s%s\n", padd, "",
// 		" \\__ \\ || | '_ \\/ -_) '_|  _/ | ' \\/ _ \\ || | _ \\/ _ \\ || |");
// 	ft_printf("%*s%s\n", padd, "",
// 		" |___/\\_,_| .__/\\___|_| |_| |_|_||_\\___/\\_, |___/\\___/\\_, |");
// 	ft_printf("%*s%s\n", padd, "",
// 		"          |_|                           |__/          |__/ ");
// }

static void	jakke_and_mikey(void)
{
	int		padd;
	char	*str;

	str = "       __      __   __           ___        __  ____ __             ";
	padd = banner_padding(ft_strlen(str));
	ft_printf("\n%*s%s\n", padd, "", str);
	ft_printf("%*s%s\n", padd, "",
		"      / ____ _/ /__/ /_____     ( _ )      /  |/  (_/ /_____  __  __");
	ft_printf("%*s%s\n", padd, "",
		" __  / / __ `/ //_/ //_/ _ \\   / __ \\/|   / /|_/ / / //_/ _ \\/ / / /");
	ft_printf("%*s%s\n", padd, "",
		"/ /_/ / /_/ / ,< / ,< /  __/  / /_/  <   / /  / / / ,< /  __/ /_/ / ");
	ft_printf("%*s%s\n", padd, "",
		"\\____/\\__,_/_/|_/_/|_|\\___/   \\____/\\/  /_/  /_/_/_/|_|\\___/\\__, /  ");
	ft_printf("%*s%s\n", padd, "",
		"                                                           /____/   ");
}

// static void	jakke_and_mikey(void)
// {
// 	int		padd;
// 	char	*str;

// 	str = "   __ ____ ____ __     ___ __  _  _ __ _  ___ __ __   ";
// 	padd = banner_padding(ft_strlen(str));
// 	ft_printf("\n%*s%s\n", padd, "", str);
// 	ft_printf("%*s%s\n", padd, "",
// 		" _(  (  __(    (  )   / __/  \\/ )( (  ( \\/ __(  (  )  ");
// 	ft_printf("%*s%s\n", padd, "",
// 		" __  / / __ `/ //_/ //_/ _ \\   / __ \\/|   / /|_/ / / //_/ _ \\/ / / /");
// 	ft_printf("%*s%s\n", padd, "",
// 		"/ /_/ / /_/ / ,< / ,< /  __/  / /_/  <   / /  / / / ,< /  __/ /_/ / ");
// 	ft_printf("%*s%s\n", padd, "",
// 		"\\____/\\__,_/_/|_/_/|_|\\___/   \\____/\\/  /_/  /_/_/_/|_|\\___/\\__, /  ");
// 	ft_printf("%*s%s\n", padd, "",
// 		"                                                           /____/   ");
// }

static void	minishell_banner(void)
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
	// super_pinoy_boy();
	jakke_and_mikey();
	minishell_banner();
}
