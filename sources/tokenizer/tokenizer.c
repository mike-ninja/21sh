/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:15:33 by jniemine          #+#    #+#             */
/*   Updated: 2022/12/19 10:25:22 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	init_params(char *line, t_token **args, size_t *pointer_n)
{
	if (!line || !*line)
		return (1);
	*pointer_n = 1;
	*args = ft_memalloc(sizeof(**args) * 2);
	(*args)[0].token = 0;
	(*args)[1].token = 0;
	return (0);
}

static void	init_variables(int *i_args, int *cur, int *start, int *end)
{
	*i_args = 0;
	*cur = 0;
	*start = 0;
	*end = 0;
}

static int	if_error(char *c, t_token *args, char *line)
{
	if (!c)
	{
		free_tokens(&args);
		ft_strdel(&line);
		return (1);
	}
	return (0);
}

static int	validity_check(char *line)
{
	if (*line == ';' || *line == '|' || *line == '&')
	{
		ft_putstr_fd("21sh: syntax error near unexpected token `", 2);
		write(2, line, 1);
		ft_putstr_fd("'\n", 2);
		return (1);
	}
	return (0);
}

t_token	*chop_line(char *line, t_token *args, size_t pointer_n)
{
	int		i_args;
	char	*c;
	int		cur;
	int		start;
	int		end;

	if (validity_check(line) || init_params(line, &args, &pointer_n))
		return (NULL);
	init_variables(&i_args, &cur, &start, &end);
	while (line[cur])
	{
		c = find_argument(line, &cur, &start, &end);
		if (if_error(c, args, line))
			return (NULL);
		init_token(c, &args[i_args], line, cur);
		++i_args;
		track_used_space(&args, i_args, &pointer_n);
		while (is_ws(line[end]))
			++end;
		cur = end;
		while (is_ws(line[cur]))
			++cur;
	}
	ft_strdel(&line);
	return (args);
}
