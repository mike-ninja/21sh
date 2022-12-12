/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion_dollar.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:57:25 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/10 18:31:39 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/**
 * It counts the number of special characters in a string
 * 
 * @param str The string to be split.
 * 
 * @return The number of special characters in the string.
 */
static int	ft_special_ch_split_len(char *str)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (str[++i])
	{
		if (!i || (ft_isspecial(str[i]) && str[i] != '_'))
			len++;
	}
	return (len);
}

/**
 * It splits a string intovan array of strings, where each string is a word, and
 * a word is defined as a sequence of characters that are not special characters
 * 
 * @param str the string to be split
 * 
 * @return A pointer to a pointer to a char.
 */
static char	**ft_special_ch_split(char *str)
{
	int		i;
	int		j;
	char	**ret;

	j = 0;
	ret = (char **)ft_memalloc(sizeof(char *) * (ft_special_ch_split_len(str) + 1));
	while (*str)
	{
		i = 0;
		if (ft_isspecial(str[i]) && str[i] != '_')
			i++;
		while (str[i] && (!ft_isspecial(str[i]) || str[i] == '_'))
			i++;
		ret[j++] = ft_strsub(str, 0, i);
		str += i;
	}
	ret[j] = NULL;
	return (ret);
}

/**
 * It takes a string, finds the first instance of a dollar sign, and replaces 
 * it with the value of the environment variable that follows the dollar sign
 * 
 * @param sesh the session struct
 * @param buff the buffer to write to
 * @param arg the string to be parsed
 */
static void	ft_find_env(t_session *sesh, char *buff, char *arg)
{
	char	*key;
	char	**env;
	int		key_len;

	key_len = 0;
	while (arg[key_len] && !ft_isspace(arg[key_len]))
		key_len++;
	key = ft_strsub(arg, 1, key_len - 1);	
	env = ft_env_get(sesh, key);
	if (env)
		ft_strcat(buff, ft_strchr(*env, '=') + 1);
	if (arg[key_len])
		ft_strcat(buff, arg + key_len);
	ft_strdel(&key);
}

/**
 * It takes a string, splits it on special characters, and then replaces any
 * dollar signs with the value of the environment variable that follows it.
 * 
 * @param sesh the session struct
 * @param str the string to be expanded
 * 
 * @return A string
 */
char	*ft_expansion_dollar(t_session *sesh, char *str)
{
	int		i;
	char	buff[BUFF_SIZE];
	char	**split_dollar;

	i = -1;
	if (!ft_strcmp(str, "$$"))
		return (ft_itoa(getpid()));
	ft_bzero(buff, BUFF_SIZE);
	split_dollar = ft_special_ch_split(str);
	while (split_dollar[++i])
	{
		if (*split_dollar[i] == '$' && ft_strlen(split_dollar[i]) > 1)
			ft_find_env(sesh, buff, split_dollar[i]);	
		else
			ft_strcat(buff, split_dollar[i]);
		ft_strdel(&split_dollar[i]);
	}
	ft_memdel((void **)&split_dollar);
	return (ft_strdup(buff));
}
