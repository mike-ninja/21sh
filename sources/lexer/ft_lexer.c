/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:05:26 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/29 13:40:51 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char	*ft_lexer(t_term *t)
{
	char	*new;

	new = ft_strtrim(t->inp);
	if (!*new)
		ft_strdel(&new);
	new = ft_heredoc(t, new);
	return (new);
}
