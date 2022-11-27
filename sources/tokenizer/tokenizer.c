/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:15:33 by jniemine          #+#    #+#             */
/*   Updated: 2022/11/27 20:38:31 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	is_ws(char c)
{
	return (c == ' ' || c == '\t' || c == '\v'
		|| c == '\f' || c == '\r');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	is_nl(char c)
{
	return (c == '\n');
}

int	is_varchr(char c)
{
	return (ft_isalnum(c) || c == '_');
}

/* cant be static */
void free_token(t_token *token)
{
	ft_memdel((void **)&token->value);
}

/*	See if one of the characters from seperators array can be found before whitespace
	from the haystack */
char *is_infuture(char *haystack, char *seperators)
{
	int i_sep;
	int	i_hay;

	i_sep = 0;
	i_hay = 0;
	while (haystack[i_hay] && !is_ws(haystack[i_hay]))
	{
		while (seperators[i_sep])
		{
			if (haystack[i_hay] == seperators[i_sep++])
				return (&haystack[i_hay]);
		}
		i_sep = 0;
		++i_hay;
	}
	return (NULL);
}

void	track_used_space(t_token **args, size_t current_pointer_n
	, size_t *max_pointer_n)
{
	size_t	new_size;
	size_t	growth;
	t_token	*new_args;
	size_t	i;

	growth = 2;
	i = 0;
	if (current_pointer_n >= *max_pointer_n)
	{
		new_size = sizeof(**args) * ((*max_pointer_n)
				+ ((*max_pointer_n) * growth));
		new_args = (t_token *)ft_memalloc(new_size);
		while (i <= current_pointer_n)
		{
			new_args[i] = (*args)[i];
			++i;
		}
		*max_pointer_n = (*max_pointer_n) * growth;
		free(*args);
		*args = new_args;
	}
}

/* TODO add rest */
int	is_seperator(char c)
{
	return (is_nl(c) || c == '|' || c == '>' || c == '<'
			|| c == ';');

}

static char *find_argument_until_seperator(char **line, int *i)
{
	char	*infuture;

	infuture = NULL;
//	if ((*line)[*i] == '<' || (*line)[*i] == '>')
//	{
//		if ((*line)[(*i) + 1] == '&')
//			++(*i);
//		else
//		{
//			while ((*line)[(*i) + 1] && (*line)[*i] == (*line)[(*i) + 1])
//				++(*i);
//			if (*i > 0 && (*line)[*i] == (*line)[(*i) - 1])
//				++(*i);
//		}
//	}
	while ((*line)[*i])
	{
		infuture = is_infuture(&(*line)[*i], "><");
		if (infuture || is_seperator((*line)[*i]))
			break ;
		++(*i);
	}
	if (*i == 0 && infuture)
	{
		while ((*line)[*i] && !is_ws((*line)[*i]))
			++(*i);
		return (infuture);
	}
//	else
//		while ((*line)[*i] && !is_seperator((*line)[*i]))
//		 	++(*i);
	if (*i == 0 && is_seperator((*line)[*i]))
		++(*i);
	return (NULL);
}

/* exceptions are [NOTWS]["] and ["][NOTWS] and [\][WS] */
char	*find_argument(char **line, char *seperator)
{
	int		i;
	char	*ret;

	i = 0;
	ret = find_argument_until_seperator(line, &i);
	if (ret && (*ret == '<' || *ret == '>'))
	{
		*seperator = *ret;
		ret = *line;
		(*line) += i;
		while (*line <= ret && !(is_ws(*ret)))
			--ret;
		i = 0;
		while (ret[i] && !is_ws(ret[i]))
			++i;
		return (ft_strndup(ret, i));
	}
	if (!ret)
		ret = ft_strndup((*line), i);
	if (!ret)
		ft_exit_no_mem(1);
	(*line) += i;
	return (ret);
}

void	set_token_values(t_token *token, int token_id, char *value)
{
	token->token = token_id;
	if (value)
		token->value = value;
}

/* TODO add support for && and || while ur at it */
/*	TODO 2randomfile>something because source is not only numbers it is assumed to be filename*/
/* Add ( and ) */
/* Make unit tests */
t_token	*chop_line(char *line, t_token *args, size_t pointer_n)
{
	size_t	i_args;
	char	*argument;
	char	seperator;

	i_args = 0;
	while (*line)
	{
			seperator = 0;
			argument = find_argument(&line, &seperator);
			if (ft_strequ(argument, "\n"))
				set_token_values(&args[i_args], NEWLINE, argument);
			else if (*argument == '|')
				set_token_values(&args[i_args], PIPE, argument);
			else if (seperator == '>' || seperator == '<')
				set_token_values(&args[i_args], REDIR, argument);
			else if (*argument == ';')
				set_token_values(&args[i_args], SEMICOLON, argument);
			else
				set_token_values(&args[i_args], WORD, argument);
		++i_args;
		track_used_space(&args, i_args, &pointer_n);
		while (is_ws(*line))
			++line;
	}
	return (args);
}
