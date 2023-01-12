/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_print_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:28:50 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/12 13:46:02 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void print_tokens(t_token *tokens)
{
	int i;

	i = 0;
	ft_printf("------------------ TOKEN DEBUG ------------------\n");
	while(tokens[i].token)
	{
		ft_printf("TOKEN: [%d], VALUE: [%s]\n", tokens[i].token, tokens[i].value);
		++i;
	}
	ft_printf("------------------ TOKEN DEBUG ------------------\n");
}
