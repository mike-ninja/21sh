/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:15:33 by jniemine          #+#    #+#             */
/*   Updated: 2022/11/21 14:36:40 by jniemine         ###   ########.fr       */
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

static void	find_argument_until_seperator(char **line, int *i)
{
	char	quote;

	quote = 0;
	while ((*line)[*i] && !is_seperator((*line)[*i]))
	{
	 	++(*i);
	}
	if (*i == 0 && is_seperator((*line)[*i]))
		++(*i);
}

/* exceptions are [NOTWS]["] and ["][NOTWS] and [\][WS] */
char	*find_argument(char **line)
{
	int		i;
	char	*ret;

	i = 0;
	find_argument_until_seperator(line, &i);
//	if (i > 1 && (*line)[i] == '\n')
//		--i;
//	else if ((*line)[i] == '\n')
//		i = 1;
	ret = ft_strndup((*line), i);
	if (!ret)
		ft_exit_no_mem(1);
	(*line) += i;
	return (ret);
}

void	set_token_values(t_token *token, char *token_id, char *value)
{
	if (token_id)
		token->token = token_id;
	if (value)
		token->value = value;
	else
		token->value = ft_strdup(token_id);
}

t_token	*chop_line(char *line, t_token *args, size_t pointer_n)
{
	size_t	i_args;
	char	*argument;

	i_args = 0;
	while (*line)
	{
			argument = find_argument(&line);
			if (ft_strequ(argument, "\n"))
				set_token_values(&args[i_args], ft_strdup("NEWLINE"), argument);
			else if (*argument == '|')
			{
				set_token_values(&args[i_args], ft_strdup("PIPE"), argument);
				++line;
			}
			else if (*argument == '>' || *argument == '<')
			{
				// TODO handle >> and << increment until not whitespace
				// JUMP over int find_argument
				set_token_values(&args[i_args], ft_strdup("REDIR"), argument);
				++line;
			}
			else
				set_token_values(&args[i_args], ft_strdup("WORD"), argument);
		++i_args;
		track_used_space(&args, i_args, &pointer_n);
		while (is_ws(*line))
			++line;
	}
		/*debugger */
	i_args = 0;
	while (args[i_args].token)
	{
		ft_printf("Token: %s and value: %s\n", args[i_args].token, args[i_args].value);
		++i_args;
	}
	return (args);
}
