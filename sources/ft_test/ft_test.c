/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:50:32 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/23 13:55:14 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
	ERRORS:
		If more than 3 params (two operands and operator I.E file1 -nt file2 is the max)
			msg: 21sh: test: too many arguments
		If 3 params, it is expected that second param is one of the binary operators, first and third are treated as operands. If not:
			msg: 21sh: <second param>: binary operator expected
		If 2 params, it is expected that first param is one of the unary operators, second one is treated as operand. If not:
			msg: 21sh: <first param>: unary operator expected
		Only one operator is allowed, so for example in: test -fe, -fe is treated as operand.
*/
static int validate_input(t_session *sesh, char **cmd)
{
	int		argc;
	int		punctuation;

	punctuation = 0;
	if (ft_strequ(cmd[1], "!"))
		punctuation = 1;
	argc = ft_arrlen(cmd);
	if (argc > (4 + punctuation))
		ft_err_print(NULL, "test", "too many arguments", 2);
	else if (argc == (4 + punctuation) && !is_binary(cmd[3 + punctuation]))
		ft_err_print("test", cmd[3 + punctuation], "binary operator expected", 2);
	else if (argc == (3 + punctuation) && !is_unary(cmd[1 + punctuation]))
		ft_err_print("test", cmd[1 + punctuation], "unary operator expected", 2);
	else
		return (0);
	return (1);
}

//	-c, -d, -e, -f, -g, -L, -p, -r, -S, -s, -u, -w, -x, -z, !
static int operator_dispatcher(char **cmd)
{
	if (ft_strequ(cmd[1], "-c"))
		return(ft_test_c(cmd));
	else if (ft_strequ(cmd[1], "-d"))
		return(ft_test_d(cmd));
	else if (ft_strequ(cmd[1], "-e"))
		return(ft_test_e(cmd));
	else if (ft_strequ(cmd[1], "-f"))
		return(ft_test_f(cmd));
	else if (ft_strequ(cmd[1], "-g"))
		return(ft_test_g(cmd));
	else if (ft_strequ(cmd[1], "-L"))
		return(ft_test_capital_l(cmd));
	else if (ft_strequ(cmd[1], "-p"))
		return(ft_test_p(cmd));
	else if (ft_strequ(cmd[1], "-r"))
		return(ft_test_r(cmd));
	else if (ft_strequ(cmd[1], "-S"))
		return(ft_test_capital_s(cmd));
	else if (ft_strequ(cmd[1], "-s"))
		return(ft_test_s(cmd));
	else if (ft_strequ(cmd[1], "-u"))
		return(ft_test_u(cmd));
	else if (ft_strequ(cmd[1], "-w"))
		return(ft_test_w(cmd));
	else if (ft_strequ(cmd[1], "-x"))
		return(ft_test_x(cmd));
	else if (ft_strequ(cmd[1], "-z"))
		return(ft_test_z(cmd));
	return (1);
}

int ft_test(t_session *sesh, char **cmd)
{
	sesh->exit_stat = 1;
	if (validate_input(sesh, cmd))
		return (0);
	sesh->exit_stat = operator_dispatcher(cmd);
	return (0);
}
