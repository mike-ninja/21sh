/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:50:32 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/16 18:57:10 by jniemine         ###   ########.fr       */
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

	argc = ft_arrlen(cmd);
	if (argc > 4)
		ft_err_print(NULL, "test", "too many arguments", 2);
	else if (argc == 4 && !is_binary(cmd[3]))
		ft_err_print("test", cmd[3], "binary operator expected", 2);
	else if (argc == 3 && !is_binary(cmd[1]))
		ft_err_print("test", cmd[1], "unary operator expected", 2);
	else
		return (0);
	sesh->exit_stat = 1;
	return (1);
}

int ft_test(t_session *sesh, char **cmd)
{
	sesh->exit_stat = 0;
	if (validate_input(sesh, cmd))
		return (0);
	return (1);
}
