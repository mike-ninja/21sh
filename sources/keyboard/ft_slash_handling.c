/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_slash_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 17:37:14 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/19 17:38:28 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void    ft_slash_handling(t_term *t)
{
    ssize_t i;

    i = t->index - 1;
    if (t->ch == '\\' && t->index == t->bytes)
    {
        while (i && t->inp[i] == '\\')
            i--;
        if ((t->index - i) % 2)
            t->slash = 1;
        else
            t->slash = 0;
    }

}
