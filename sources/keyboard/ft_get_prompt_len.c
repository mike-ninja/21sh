/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_prompt_len.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:59:55 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/11 15:28:40 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

ssize_t	ft_get_prompt_len(t_term *t, ssize_t row)
{
	ssize_t	prompt_len;

	prompt_len = 0;
	if (!row)
		prompt_len = t->prompt_len;
	else if (ft_is_prompt_line(t, row))
		prompt_len = t->m_prompt_len;
	return (prompt_len);
}
