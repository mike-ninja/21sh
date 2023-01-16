/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 09:30:04 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/16 18:48:38 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

// static void	init_sig_action(struct sigaction *sig_action)
// {
// 	sig_action->sa_handler = sig_session_handler;
	
// 	sigaction(SIGINT, sig_action, NULL);
// }

void	main_loop(t_session *sesh)
{
	int	status;

	status = 1;
	sesh->term->clipboard.buff = NULL;
	while (status)
	{
		sesh->process_control = 0;
		ft_init_signals();
		// init_sig_action(&sesh->sig_action);
		sesh->orig_termios = ft_raw_enable();
		if (ft_keyboard(sesh->term) == 1)
		{
			ft_history_write_to_file(sesh->term);
			status = 0;
		}
		ft_raw_disable(sesh->orig_termios);
		if (*(sesh->term->inp))
		{
			sesh->line = ft_lexer(sesh->term);
			sesh->tokens = chop_line(sesh->line, sesh->tokens, 1);
			sesh->head = build_tree(sesh->tokens);
			if (sesh->head && ((t_semicolon *)sesh->head)->left)
				exec_tree(sesh->head, &sesh->env, sesh->terminal, sesh);
			shell_end_cycle(sesh);
		}
	}
}

int	main(void)
{
	t_session		sesh[1];

	ft_getent();
	banner_print();
	ft_session_init(sesh);
	ft_history_get(sesh->term);
	main_loop(sesh);
	ft_strdel(&sesh->terminal);
	return (0);
}
