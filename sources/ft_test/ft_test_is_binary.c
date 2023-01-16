/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_is_binary.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:31:13 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/16 18:41:03 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
	!=, -eq, -ne, -ge, -lt, -le, =
*/
int is_binary(char *str)
{
	return (ft_strequ(str, "!=") || ft_strequ(str, "-eq")
			|| ft_strequ(str, "-ne") || ft_strequ(str, "-ge")
			|| ft_strequ(str, "-lt") || ft_strequ(str, "-le")
			|| ft_strequ(str, "="));
}
