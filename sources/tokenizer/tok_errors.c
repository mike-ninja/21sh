/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:04:42 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/06 17:15:32 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	control_op_error_split(char *str)
{
	if (ft_strnequ(str, ";", 1))
		ft_err_print(NULL, "syntax error near unexpected token",
			"`;'", 1);
	else if (ft_strnequ(str, "(", 1))
		ft_err_print(NULL, "syntax error near unexpected token",
			"`('", 1);
	else if (ft_strnequ(str, ")", 1))
		ft_err_print(NULL, "syntax error near unexpected token",
			"`)'", 1);
	else if (*str == '\0')
		ft_err_print(NULL, "syntax error near unexpected token",
			"`newline'", 1);
	else
		return (0);
	return (1);
}

int	control_op_error(char *str)
{
	if (ft_strnequ(str, "||", 2))
		ft_err_print(NULL, "syntax error near unexpected token",
			"`||'", 2);
	else if (ft_strnequ(str, "|", 1))
		ft_err_print(NULL, "syntax error near unexpected token",
			"`|'", 1);
	else if (ft_strnequ(str, "&&", 2))
		ft_err_print(NULL, "syntax error near unexpected token",
			"`&&'", 2);
	else if (ft_strnequ(str, "&", 1))
		ft_err_print(NULL, "syntax error near unexpected token",
			"`&'", 1);
	else if (ft_strnequ(str, ";;", 2))
		ft_err_print(NULL, "syntax error near unexpected token",
			"`;;'", 2);
	return (control_op_error_split(str));
}

int	redir_error(char *str)
{
	if (ft_strnequ(str, ">>", 2))
		ft_err_print(NULL, "syntax error near unexpected token",
			"`>>'", 2);
	else if (ft_strnequ(str, "<<", 2))
		ft_err_print(NULL, "syntax error near unexpected token",
			"`<<'", 2);
	else if (ft_strnequ(str, "<", 1))
		ft_err_print(NULL, "syntax error near unexpected token",
			"`<'", 2);
	else if (ft_strnequ(str, ">", 1))
		ft_err_print(NULL, "syntax error near unexpected token",
			"`>'", 1);
	else
		return (0);
	return (1);
}
