/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:05:26 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/18 20:53:57 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char	*ft_lexer(t_term *t)
{
	int		i;
	int		k;
	size_t	len;
	char	*new;

	i = -1;
	new = ft_strtrim(t->inp);
	if (!*new)
		ft_strdel(&new);
	new = ft_heredoc(t, new);
	return (new);
}
