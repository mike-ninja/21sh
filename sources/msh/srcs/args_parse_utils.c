/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parse_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:39:30 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/18 16:33:24 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	arg_qty_loop(char *line_cpy, int *len)
{
	while (line_cpy)
	{
		if (*line_cpy == '"')
		{
			line_cpy++;
			ft_strsep(&line_cpy, "\"");
		}
		else if (*line_cpy == '\'')
		{
			line_cpy++;
			ft_strsep(&line_cpy, "\'");
		}
		else
			ft_strsep(&line_cpy, " ");
		line_cpy = skip_whitespace(line_cpy);
		len[0]++;
	}
}

static void	qoute_removal(char **arg)
{
	int		i;
	int		j;
	char	line[BUFF_SIZE];

	i = 0;
	j = 0;
	ft_bzero(line, BUFF_SIZE);
	while (arg[0][i])
	{	
		while (arg[0][i] && (arg[0][i] == '"' || arg[0][i] == '\''))
			i++;
		line[j++] = arg[0][i++];
		while (arg[0][i] && (arg[0][i] == '"' || arg[0][i] == '\''))
			i++;
	}
	ft_strdel(arg);
	*arg = ft_strdup(line);
}

static void	qoute_parse(char **line, char **arg, int *i, char *sep)
{
	char	*tofree;

	tofree = NULL;
	line[0]++;
	arg[i[0]++] = ft_strdup(ft_strsep(&line[0], sep));
	if (line[0] && !ft_iswhitespace(line[0][0]))
	{
		tofree = arg[i[0] - 1];
		arg[i[0] - 1] = ft_strjoin(arg[i[0] - 1], ft_strsep(line, " "));
		ft_strdel(&tofree);
	}
}

void	collect_args_loop(char **args, char *line, bool *tok, int *i)
{
	while (line)
	{
		if (*line == '"')
		{
			tok[*i] = 1;
			qoute_parse(&line, args, i, "\"");
		}
		else if (*line == '\'')
		{
			tok[*i] = 0;
			qoute_parse(&line, args, i, "\'");
		}
		else
		{
			tok[*i] = 1;
			args[i[0]++] = ft_strdup(ft_strsep(&line, " "));
			if (ft_strchr(args[*i - 1], '"') || ft_strchr(args[*i - 1], '\''))
				qoute_removal(&args[*i - 1]);
		}
		line = skip_whitespace(line);
	}
	args[*i] = NULL;
}
