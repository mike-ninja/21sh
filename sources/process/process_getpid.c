/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_getpid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 22:10:49 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/23 13:36:01 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static t_proc   *search_via_index(int index, t_proc *head)
{
    while (head)
    {
        if (index == head->index)
            return (head);
        head = head->next;
    }
    return (NULL);
}

static t_proc   *search_via_cmd(char *cmd, t_proc *head)
{
    t_proc  *ret;

    ret = NULL;
    while (head)
    {
        if (!ft_strcmp(cmd, *head->command))
        {
            if (ret)
                return (NULL);
            else
                ret = head;
        }
        head = head->next;
    }
    return (ret);
}

/* static t_proc   *search_via_percent_ch(char sign, t_proc *head)
{
    int count;

    count = 0;
    while (head)
    {
        if (sign == head->queue || (!head->next && !count))
            return (head);
        count++;
        head = head->next;
    }
    return (NULL);
} */

t_proc *process_getpid(int index, char *cmd, /* char sign, */ t_proc *head)
{
    if (index)
        return (search_via_index(index, head));
    if (cmd)
        return (search_via_cmd(cmd, head));
    /* if (sign)
        return (search_via_percent_ch(sign, head)); */
    return (NULL);
}
