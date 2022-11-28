/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:55:11 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/28 15:28:24 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/**
 * It counts the number of characters in a string that are not quotes
 * 
 * @param str The string to be counted.
 * 
 * @return The length of the string.
 */
static int	ft_alphalen(char *str)
{
	int	len;

	len = 0;
	if (str)
	{
		while (*str)
		{
			if (*str != '\"' && *str != '\'')
				len++;
			str++;
		}
	}
	return (len);
}

/**
 * It removes quotes from a string
 * 
 * @param str The string to be modified.
 * 
 * @return the value of the variable valid.
 */
static int	ft_quote_remove(char **str)
{
	int		i;
	int		j;
	int		valid;
	char	*new_arr;

	i = 0;
	j = -1;
	valid = 0;
	new_arr = NULL;
	if (*(*str) == '\"' || *(*str) == '\'')
	{
		if (*(*str) == '\'')
			valid = 1;
		new_arr = (char *)ft_memalloc(sizeof(char) * (ft_alphalen(*str) + 1));
		while ((*str)[++j])
		{
			if ((*str)[j] == '\"' || (*str)[j] == '\'')
				continue ;
			new_arr[i++] = (*str)[j];
		}
		new_arr[i] = '\0';
		ft_strdel(str);
		*str = new_arr;
	}
	return (valid);
}

/**
 * It splits the token value on spaces, and then for each word, it checks if
 * it contains a dollar sign. If it does, it calls ft_expansion_dollar, which
 * will expand the word. If it doesn't, it calls ft_expansion_tilde, which will
 * expand the word.
 * 
 * @param sesh the session struct
 * @param buff the buffer that will be returned
 * @param tok_valthe value of the token, which is the string to be expanded
 * 
 * @return A string
 */
static char	*ft_expansion_loop(t_session *sesh, char *buff, \
char **tok_val, char **split)
{
	int		i;
	char	*tofree;

	i = -1;
	ft_strdel(tok_val);
	while (split[++i])
	{
		if (ft_strchr(split[i], '$') && ft_strlen(split[i]) > 1)
		{
			if (!ft_quote_remove(&split[i]))
			{
				tofree = split[i];
				split[i] = ft_expansion_dollar(sesh, split[i]);
				ft_strdel(&tofree);
			}
			ft_strcat(buff, split[i]);
		}
		else
			ft_strcat(buff, ft_expansion_tilde(sesh, split[i]));
		if (split[i + 1])
			ft_strcat(buff, " ");
		ft_strdel(&split[i]);
	}
	ft_memdel((void **)&split);
	return (buff);
}

/**
 * This function expands the tokens.
 * 
 * @param sesh The session struct.
 * 
 * @return The expanded tokens.
 */
void	ft_expansion(t_session *sesh)
{
	int		i;
	char	buff[BUFF_SIZE];

	i = -1;
	while (sesh->tokens[++i].token)
	{
		ft_printf("DEBUG: %s\n", sesh->tokens[i].value);
		ft_bzero(buff, BUFF_SIZE);
		sesh->tokens[i].value = ft_strdup(ft_expansion_loop(sesh, buff, \
			&sesh->tokens[i].value, ft_strsplit(sesh->tokens[i].value, ' ')));
	}
}
