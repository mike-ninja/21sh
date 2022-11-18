/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:55:57 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/18 10:36:06 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	arg_qty(char *line)
{
	int		len;
	char	*line_cpy;
	char	*tofree;

	len = 0;
	line_cpy = ft_strdup(line);
	tofree = line_cpy;
	line_cpy = skip_whitespace(line_cpy);
	arg_qty_loop(line_cpy, &len);
	ft_strdel(&tofree);
	return (len);
}

static void	collect_args(char **args, char **line, bool	*tok)
{
	int		i;

	i = 0;
	*line = skip_whitespace(*line);
	collect_args_loop(args, *line, tok, &i);
}

int	get_args(t_session *sesh, char **line)
{
	int	len;

	len = arg_qty(*line);
	sesh->tok->arg = (char **)malloc(sizeof(char *) * (len + 1));
	if (len)
		sesh->tok->tok = (bool *)ft_memalloc(sizeof(bool) * (len));
	if (!sesh->tok->arg || (!sesh->tok->tok && len))
		ft_exit_no_mem(1);
	collect_args(sesh->tok->arg, line, sesh->tok->tok);
	tilda_parse(sesh);
	dollar_parse(sesh);
	return (RESET);
}
