/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 20:34:50 by jakken            #+#    #+#             */
/*   Updated: 2022/12/28 19:48:14 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

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

int	is_seperator(char c)
{
	return (c == '|' || c == '>' || c == '<'
		|| c == ';');
}
