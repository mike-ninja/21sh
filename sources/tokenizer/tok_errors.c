/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:04:42 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/18 17:21:29 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	test_if_error_split(char *line, char *str, int err_flag)
{
	if (!err_flag && (is_seperator(*line) && *line != ';') && *str == '\0')
		err_flag = ft_err_print(NULL, "syntax error near unexpected token",
				"`newline'", 1);
	else if (!err_flag && is_seperator(*line) && *str && is_seperator(*str))
	{
		*(str + 1) = '\0';
		err_flag = ft_err_print(NULL, "syntax error near unexpected token",
				str, 1);
	}
	else if (!err_flag)
		return (0);
	return (1);
}

static int	control_op_error_split(char *str)
{
	if (*str == ';' && ft_strnequ(str + 1, ";", 1))
		ft_err_print(NULL, "syntax error near unexpected token",
			"`;'", 1);
	else if (*str == ft_strnequ(str + 1, "(", 1))
		ft_err_print(NULL, "syntax error near unexpected token",
			"`('", 1);
	else if (ft_strnequ(str + 1, ")", 1))
		ft_err_print(NULL, "syntax error near unexpected token",
			"`)'", 1);
	else if (*str != '&' && *str != ';' && *(str + 1) == '\0')
		ft_err_print(NULL, "syntax error near unexpected token",
			"`newline'", 1);
	else
	char	*str;
	int		err_flag;

	str = NULL;
	err_flag = 0;
	if (*line && *line != '<' && *line != '>')
		str = line + 1;
	else
		return (0);
	if (!err_flag && *line == '|' && (*str && *str == '|'))
		err_flag = ft_err_print(NULL, "syntax error near unexpected token",
				"`|'", 1);
	else if (!err_flag && *str && ft_strnequ(str, ";;", 2))
		err_flag = ft_err_print(NULL, "syntax error near unexpected token",
				"`;;'", 2);
	else if (!err_flag && *str && ft_strnequ(str, ";", 1))
		err_flag = ft_err_print(NULL, "syntax error near unexpected token",
				"`;'", 1);
	return (test_if_error_split(line, str, err_flag));
}

static int	redir_error_split(char *str, int err_flag)
{
	if (!err_flag && ft_strnequ(str, "&", 1))
		err_flag = ft_err_print(NULL, "syntax error near unexpected token",
				"`&'", 1);
	else if (!err_flag && is_seperator(*str))
	{
		*(str + 1) = '\0';
		err_flag = ft_err_print(NULL, "syntax error near unexpected token",
				str, 1);
	}
	else if (!err_flag)
		return (0);
	return (1);
}

int	control_op_error(char *str)
{
	if (*str == '|' && ft_strnequ(str + 1, "||", 2))
		ft_err_print(NULL, "syntax error near unexpected token",
			"`||'", 2);
	else if (*str == '|' && ft_strnequ(str + 1, "|", 1))
		ft_err_print(NULL, "syntax error near unexpected token",
			"`|'", 1);
	else if (*str == '&' && ft_strnequ(str + 1, "&&", 2))
		ft_err_print(NULL, "syntax error near unexpected token",
			"`&&'", 2);
	else if (*str == '&' && ft_strnequ(str + 1, "&", 1))
		ft_err_print(NULL, "syntax error near unexpected token",
			"`&'", 1);
	else if (*str == ';' && ft_strnequ(str + 1, ";;", 2))
		ft_err_print(NULL, "syntax error near unexpected token",
			"`;;'", 2);
	return (control_op_error_split(str));
}

int	redir_error(char *str)
{
	int	err_flag;

	err_flag = 0;
	if (!*str)
		return (0);
	if (!err_flag && ft_strnequ(str, ">>", 2))
		err_flag = ft_err_print(NULL, "syntax error near unexpected token",
				"`>>'", 2);
	else if (!err_flag && ft_strnequ(str, "<<", 2))
		err_flag = ft_err_print(NULL, "syntax error near unexpected token",
				"`<<'", 2);
	else if (!err_flag && ft_strnequ(str, "<", 1))
		err_flag = ft_err_print(NULL, "syntax error near unexpected token",
				"`<'", 2);
	else if (!err_flag && ft_strnequ(str, ">", 1))
		err_flag = ft_err_print(NULL, "syntax error near unexpected token",
				"`>'", 1);
	return (redir_error_split(str, err_flag));
}
