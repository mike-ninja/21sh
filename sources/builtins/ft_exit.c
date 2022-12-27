/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 08:23:30 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/27 13:53:48 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ft_exit(t_session *sesh, int status)
{
	ft_printf("{RED}exit{RESET}\n");
	ft_history_write_to_file(sesh->term);
	ft_raw_disable(sesh->orig_termios);
	if (sesh->term->clipboard.buff)
		ft_strdel(&sesh->term->clipboard.buff);
	shell_end_cycle(sesh);
	exit(status);
}
