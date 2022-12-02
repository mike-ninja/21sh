/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:15:33 by jniemine          #+#    #+#             */
/*   Updated: 2022/12/02 21:43:04 by jniemine         ###   ########.fr       */
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

void free_token(t_token *token)
{
	ft_memdel((void **)&token->value);
}

void free_tokens(t_token *tokens)
{
	int i;

	i = 0;
	while (tokens && tokens[i].token)
	{
		free(tokens[i].value);
		tokens[i].value = NULL;
		tokens[i].token = 0;
		++i;
	}
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
	while (haystack[i_hay] && is_ws(haystack[i_hay]))
		++i_hay;
	while (seperators[i_sep])
	{
		if (haystack[i_hay] == seperators[i_sep++])
			return (&haystack[i_hay]);
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

static char *find_argument_until_seperator(char *line, int *i, int *start, int *end)
{
	char	*infuture;

	infuture = NULL;
	while ((line)[*i])
	{
		infuture = is_infuture(&(line[(*i)]), "><");
		if (infuture || is_seperator((line)[*i]))
		{
			*start = *i;
			break ;
		}
		++(*i);
	}
	*end = *i;
	if (*i == 0 && infuture)
	{
		while ((line)[*i] && !is_ws((line)[*i]))
			++(*i);
		return (infuture);
	}
	else
		while ((line)[*end] && !is_ws((line)[*end]))
		 	++(*end);
	if (*i == 0 && is_seperator((line)[*i]))
		++(*i);
	return (NULL);
}

int operator_len(char *op)
{
	if (is_seperator(*op))
	{
		if (op[0] == '>' && ((op[1] == '>' || op[1] == '&')
			|| (op[0] == '<' && (op[1] == '<' || op[1] == '&'))))
			return (2);
		return (1);
	}
	return (0);
}

char	*if_redir(char *line, int *i, int *start, int *end)
{
	int digits;

	digits = 0;
	while (ft_isdigit(line[*i + digits]))
		++digits;
	if (line[*i + digits] == '>' || line[*i + digits] == '<')
	{
		*start = *i;
		*i = *i + digits;
		*end = *i + digits + 1;
		if (line[*end] == '<' || line[*end] == '>' || line[*end] == '&')
			++(*end);
		if (line[*end] == '<' || line[*end] == '>' || line[*end] == '&')
		{
			ft_printf("21sh: syntax error near `%c'", line[*end]);
			//Freeall
			return (NULL);
		}
		while (line[*end] && is_ws(line[*end]))
			++(*end);
		while (line[*end] && !is_ws(line[*end]) && !is_seperator(line[*end]))
			++(*end);
		return(ft_strsub(line, *start, *end - *start));
	}
	return (NULL);
}

/* exceptions are [NOTWS]["] and ["][NOTWS] and [\][WS] */
char	*find_argument(char *line, int *i, int *start, int *end)
{
	char	*ret;
	int		digits;
//	ret = find_argument_until_seperator(line, i, start, end);
//	if (is_seperator(line[*start]) && line[*start] != '>' && line[*start] != '<')
//		*end += operator_len(&line[*start]);
//	else
	digits = 1;
	ret = if_redir(line, i, start, end);
	if (ret)
		return (ret);
	if (!is_seperator(line[*end]))
	{
		while (line[*end] && !is_seperator(line[*end]))
			++(*end);
		if ((line[*end] == '>' || line[*end] == '<')
			&& (*end) > 0)
		{
			while (ft_isdigit(line[*end - digits]))
				++digits;
			if (*end - digits == 0 || is_ws(line[*end - digits]))
			{
				*end -= digits;
//				*i = *end;
			}
		}
		else if (is_seperator(*end > 0 && line[*end]))
			--(*end);
	}
	else
		*end += operator_len(&line[*end]);
	ret = ft_strsub(line, *i, *end - *i);
//	if (!ret)
//		ret = ft_strndup(line + *start, *i);
//	if (!ret)
//		ft_exit_no_mem(1);
	return (ret);
}

void	set_token_values(t_token *token, int token_id, char *value)
{
	token->token = token_id;
	if (value)
		token->value = value;
}


/*
static void redir_or_aggregation(char *line, int prev, int cur)
{
	while (prev < cur && )
}
*/

/* TODO add support for && and || while ur at it */
/*	TODO 2randomfile>something because source is not only numbers it is assumed to be filename*/
/* Add ( and ) */
/* Make unit tests */
//TODO make token node for fd aggregation
//TODO >& must have digit target
//TODO combine all word tokens before ; as one...
// TODO Pick up only touching digits before
t_token	*chop_line(char *line, t_token *args, size_t pointer_n)
{
	int		i_args;
	char	*c;
	int		cur;
	int		start;
	int		end;

	if (!line)
		return (NULL);
	i_args = 0;
	cur = 0;
	start = 0;
	end = 0;
	/*Init every time*/
	pointer_n = 1;
	args = ft_memalloc(sizeof(*args) * 2);
	args[0].token = 0;
	args[1].token = 0;
	while (line[cur])
	{
		c = find_argument(line, &cur, &start, &end);
		if (*c == '\n')
			set_token_values(&args[i_args], NEWLINE, c);
		else if (*c == '|')
			set_token_values(&args[i_args], PIPE, c);
		else if (line[cur] == '>' || line[cur] == '<')
		{
			if (line[cur + 1] == '&')
				set_token_values(&args[i_args], AGGREGATION, c);
			else
				set_token_values(&args[i_args], REDIR, c);
		}
		else if (*c == ';')
			set_token_values(&args[i_args], SEMICOLON, c);
		else
			set_token_values(&args[i_args], WORD, c);
		++i_args;
		track_used_space(&args, i_args, &pointer_n);
		cur = end;
		while (is_ws(line[cur]))
			++cur;
	}
	/*Debug*/
//	 i_args = 0;
//	 while (args[i_args].token)
//	 {
//	 	ft_printf("TOK: %s tok: %d\n", args[i_args].value, args[i_args].token);
//	 	++i_args;
//	 }
	return (args);
}
