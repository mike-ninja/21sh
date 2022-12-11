/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 08:23:30 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/11 16:19:49 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ft_exit(t_session *sesh, int status)
{
	ft_raw_disable(sesh->orig_termios);
	shell_end_cycle(sesh);
	exit(status);
}
