/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:42:17 by jniemine          #+#    #+#             */
/*   Updated: 2022/12/14 14:47:31 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	free_token(t_token *token)
{
	ft_memdel((void **)&token->value);
}

void	free_tokens(t_token *tokens)
{
	int	i;

	i = -1;
	while (tokens && tokens[++i].token)
	{
		ft_strdel(&tokens[i].value);
		tokens[i].token = 0;
	}
	ft_memdel((void **)&tokens);
}
