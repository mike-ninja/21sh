/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:44:55 by jniemine          #+#    #+#             */
/*   Updated: 2022/12/14 14:45:14 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	debug_tokens(t_token *args)
{
	int	i_args;

	i_args = 0;
	while (args[i_args].token)
	{
		ft_printf("TOK: %s tok: %d\n", args[i_args].value, args[i_args].token);
		++i_args;
	}
	exit(1);
}
