/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 09:30:04 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/15 19:25:21 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	main(int argc, char **argv)
{
	int				status;
	t_session		sesh[1];
	int				test_flag;

	test_flag = 0;
	if (argc && argc > 1 && ft_strequ(argv[1], "-c"))
		test_flag = 1;
	status = 1;
	ft_getent();
	if (!test_flag)
		sesh->orig_termios = ft_raw_enable();
	if (!test_flag)
		banner_print();
	if (!test_flag)
		ft_raw_disable(sesh->orig_termios);
	ft_session_init(sesh);
	ft_history_get(&sesh->term);
	while (status)
	{
		if (!test_flag)
		{
			sesh->orig_termios = ft_raw_enable();
			if (ft_keyboard(&sesh->term) == 1)
				status = 0;
			ft_raw_disable(sesh->orig_termios);
		}
		if (*(sesh->term->inp))
		{
			if (!test_flag)
				sesh->line = ft_lexer(&sesh->term);
			else
				sesh->line = str_from_arr(&argv[2]);
			sesh->tokens = chop_line(sesh->line, sesh->tokens, 1);
			/*DEBUG*/
			// t_token *tmp = sesh->tokens;

			// while (tmp->token)
			// {
			// 	ft_putstr("[");
			// 	ft_putstr(tmp->value);
			// 	ft_putstr("]");
			// 	ft_putchar(' ');
			// 	tmp++;
			// }
			// ft_putchar('\n');
			/*DEBUG*/
			sesh->head = build_tree(sesh->tokens);
			if (sesh->head && ((t_semicolon *)sesh->head)->left)
			{
				exec_tree(sesh->head, &sesh->env, sesh->terminal, sesh);
			}
			shell_end_cycle(sesh);
			if (test_flag)
				status = 0;
		}
	}
	ft_strdel(&sesh->terminal);

	return (0);
}
