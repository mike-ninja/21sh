/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 09:30:04 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/08 16:46:10 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	main(int argc, char **argv)
{
	t_term			term;
	char			*line;
	int				status;
	t_session		sesh[1];
	int				test_flag;

	test_flag = 0;
	if (argc && argc > 1 && ft_strequ(argv[1], "-c"))
		test_flag = 1;
	status = 1;
	line = NULL;
	ft_getent();
	if (!test_flag)
		sesh->orig_termios = ft_raw_enable();
	if (!test_flag)
		banner_print();
	ft_session_init(sesh);
	t_token	*tmp;
	while (status)
	{
		if (!test_flag)
			ft_keyboard(&term);
		if (!test_flag)
			line = term.inp;
		else
			line = str_from_arr(&argv[2]);
		sesh->tokens = chop_line(line, sesh->tokens, 1);
		sesh->head = build_tree(sesh->tokens);
		/*debug*/
		// t_token *tmp = sesh->tokens;

		// while (tmp->token)
		// {
		// 	ft_putchar('[');
		// 	ft_putstr(tmp->value);
		// 	ft_putchar(']');
		// 	ft_putchar('\n');
		// 	tmp++;
		// }
		if (sesh->head /*&& ft_builtins(sesh) == 1*/)
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
		ft_endcycle(sesh);
		if (test_flag)
			status = 0;
		// reset_filedescriptors(sesh);
	}
	ft_strdel(&sesh->terminal);
	if (!test_flag)
		ft_raw_disable(sesh->orig_termios);
	return (0);
}
