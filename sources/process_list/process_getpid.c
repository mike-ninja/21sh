/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_getpid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:52:07 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/11 16:22:40 by mbarutel         ###   ########.fr       */
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

static t_proc   *search_via_percent_ch(char sign, t_proc *head)
{
    int count;

    count = 0;
    while (head)
    {
        if (sign == head->job || (!head->next && !count))
            return (head);
        count++;
        head = head->next;
    }
    return (NULL);
}

t_proc *process_getpid(int index, char *cmd, char sign, t_proc *head)
{
    if (index)
        return (search_via_index(index, head));
    if (cmd)
        return (search_via_cmd(cmd, head));
    if (sign)
        return (search_via_percent_ch(sign, head));
    return (NULL);
}
