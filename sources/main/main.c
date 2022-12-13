/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 09:30:04 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/13 11:45:26 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	main(int argc, char **argv)
{
	t_term			term;
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
	ft_history_get(&term);
	while (status)
	{
		if (!test_flag)
		{
			sesh->orig_termios = ft_raw_enable();
			if (ft_keyboard(&term) == 1)
				status = 0;
			ft_raw_disable(sesh->orig_termios);
		}
		if (*term.inp)
		{
			if (!test_flag)
			{
				// sesh->line = ft_strdup(term.inp);
				sesh->line = ft_lexer(&term);
				// ft_printf("[%s]\n", sesh->line);
			}
			else
				sesh->line = str_from_arr(&argv[2]);
			sesh->tokens = chop_line(sesh->line, sesh->tokens, 1);
			/*DEBUG*/			
			t_token *tmp = sesh->tokens;

			while (tmp->token)
			{
				ft_putstr("[");
				ft_putstr(tmp->value);
				ft_putstr("]");
				ft_putchar(' ');
				tmp++;
			}
			ft_putchar('\n');
			/*DEBUG*/			
			sesh->head = build_tree(sesh->tokens);
			// if (sesh->head && ft_builtins(sesh) == 1)
			if (sesh->head)
			{
			//	if (sesh->head && sesh->head->type == CMD)
			//		execute_bin(((t_cmdnode *)sesh->head)->cmd, &sesh->env);
			//	else if (sesh->head && sesh->head->type != CMD)
				exec_tree(sesh->head, &sesh->env, sesh->terminal, sesh);
			}
			//	wait (0);
				/*		debugging		*/
	//				int i_args = -1;
	//				while (sesh->tokens[++i_args].token)
	//				{
	//					ft_putstr(sesh->tokens[i_args].value);
	//					if (sesh->tokens[i_args + 1].token)
	//						ft_putchar(' ');
	//				}
	//				ft_putchar('\n');
				/*		debugging		*/
			// }
			shell_end_cycle(sesh);
			if (test_flag)
				status = 0;
		}
		// reset_filedescriptors(sesh);
	}
	ft_strdel(&sesh->terminal);

	return (0);
}
