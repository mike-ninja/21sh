/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:09:10 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/17 23:35:19 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	test_if_error(char *line)
{
	char	*str;

	str = line + 1;
	if (*line == '|' && *str == '|')
		ft_err_print(NULL, "syntax error near unexpected token",
			"`|'", 1);
	else if (ft_strnequ(str, ";;", 2))
		ft_err_print(NULL, "syntax error near unexpected token",
			"`;;'", 2);
	else if (ft_strnequ(str, ";", 1))
		ft_err_print(NULL, "syntax error near unexpected token",
			"`;'", 1);
	else if ((is_seperator(*line) && *line != ';') && *str == '\0')
		ft_err_print(NULL, "syntax error near unexpected token",
			"`newline'", 1);
	else if (*line == ';' && is_seperator(*str))
	{
		*(str + 1) = '\0';
		ft_err_print(NULL, "syntax error near unexpected token",
			str, 1);
	}
	else
		return (0);
	return (1);
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
	else if (ft_strnequ(str, "&", 1))
		ft_err_print(NULL, "syntax error near unexpected token",
			"`&'", 1);
	else if (is_seperator(*str))
	{
		*(str + 1) = '\0';
		ft_err_print(NULL, "syntax error near unexpected token",
			str, 1);
	}
	else
		return (0);
	return (1);
}
