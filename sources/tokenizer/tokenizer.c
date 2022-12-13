/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:15:33 by jniemine          #+#    #+#             */
/*   Updated: 2022/12/13 22:01:40 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void free_tokens(t_token *tokens)
{
	int i;

	i = -1;
	while (tokens && tokens[++i].token)
	{
		ft_strdel(&tokens[i].value);
		tokens[i].token = 0;
	}
	ft_memdel((void **)&tokens);
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

int	is_seperator(char c)
{
	return (is_nl(c) || c == '|' || c == '>' || c == '<'
			|| c == ';');

}

void	set_token_values(t_token *token, int token_id, char *value)
{
	token->token = token_id;
	if (value)
		token->value = value;
}

static void	init_token(char *c, t_token *token, char *line, int cur)
{
	if (*c == '|')
		set_token_values(token, PIPE, c);
	else if (line[cur] == '>' || line[cur] == '<')
	{
		if (line[cur + 1] && line[cur + 2] && line[cur + 1] == '&'
			&& line[cur + 2] == '-')
			set_token_values(token, CLOSEFD, c);
		else if (line[cur + 1] == '&')
			set_token_values(token, AGGREGATION, c);
		else
			set_token_values(token, REDIR, c);
	}
	else if (*c == ';')
		set_token_values(token, SEMICOLON, c);
	else
		set_token_values(token, WORD, c);
}

t_token	*chop_line(char *line, t_token *args, size_t pointer_n)
{
	int		i_args;
	char	*c;
	int		cur;
	int		start;
	int		end;

	if (!line || !*line)
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
		init_token(c, &args[i_args], line, cur);
//		if (*c == '|')
//			set_token_values(&args[i_args], PIPE, c);
//		else if (line[cur] == '>' || line[cur] == '<')
//		{
//			if (line[cur + 1] && line[cur + 2] && line[cur + 1] == '&'
//				&& line[cur + 2] == '-')
//				set_token_values(&args[i_args], CLOSEFD, c);
//			else if (line[cur + 1] == '&')
//				set_token_values(&args[i_args], AGGREGATION, c);
//			else
//				set_token_values(&args[i_args], REDIR, c);
//		}
//		else if (*c == ';')
//			set_token_values(&args[i_args], SEMICOLON, c);
//		else
//			set_token_values(&args[i_args], WORD, c);
		++i_args;
		track_used_space(&args, i_args, &pointer_n);
		while (is_ws(line[end]))
			++end;
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
//	 exit(1);
	ft_strdel(&line);
	return (args);
}
