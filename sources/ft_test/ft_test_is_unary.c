/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_is_unary.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:30:29 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/16 18:39:59 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_21sh.h"

/*
	These are mandatory:
	-c, -d, -e, -f, -g, -L, -p, -r, -S, -s, -u, -w, -x, -z, !
*/
int is_unary(char *str)
{
	return (ft_strequ(str, "-c") || ft_strequ(str, "-d")
			|| ft_strequ(str, "-e") || ft_strequ(str, "-f")
			|| ft_strequ(str, "-g") || ft_strequ(str, "-L")
			|| ft_strequ(str, "-p") || ft_strequ(str, "-r")
			|| ft_strequ(str, "-S") || ft_strequ(str, "-s")
			|| ft_strequ(str, "-u") || ft_strequ(str, "-w")
			|| ft_strequ(str, "-x") || ft_strequ(str, "-z")
			|| ft_strequ(str, "!"));
}
