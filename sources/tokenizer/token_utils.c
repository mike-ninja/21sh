/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 20:34:50 by jakken            #+#    #+#             */
/*   Updated: 2022/12/13 20:37:25 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	is_ws(char c)
{
	return (c == ' ' || c == '\t' || c == '\v'
		|| c == '\f' || c == '\r');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	is_nl(char c)
{
	return (c == '\n');
}

int	is_varchr(char c)
{
	return (ft_isalnum(c) || c == '_');
}

void	free_token(t_token *token)
{
	ft_memdel((void **)&token->value);
}
