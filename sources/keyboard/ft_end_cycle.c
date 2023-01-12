/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_end_cycle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:04:06 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/12 19:03:25 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static char	*ft_strjoin_three(char *s1, char *s2, char *s3)
{
	size_t	total;
	char	*new;

	if (!s1 || !s2 || !s3)
		return (NULL);
	total = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	new = ft_strnew(total);
	if (new != NULL)
	{
		new = ft_strcpy(new, (const char *)s1);
		new = ft_strcat(new, (const char *)s2);
		new = ft_strcat(new, (const char *)s3);
	}
	return (new);
}

static void expand(t_term *t, int i, int pos, int len)
{
	char 	*begin;
	char 	*end;
	char 	*ret;

	begin = ft_strsub(t->inp, 0, i);
	end = ft_strdup(t->inp + i + len);
	ret = ft_strjoin_three(begin, t->history_arr[t->history_size - pos], t->inp + i + len);
	ft_strdel(&begin);
	ft_strdel(&end);
	ft_strclr(t->inp);
	ft_memcpy(t->inp, ret, ft_strlen(ret));
	ft_strdel(&ret);
	t->bytes += ft_strlen(t->history_arr[t->history_size - pos]) - len; //remember to not overflow bytes (static array)
}

static void	ft_history_expantion(t_term *t)
{
	int		i;
	int		x;

	x = 0;
	i = -1;
	while (t->inp[++i])
	{
		if (t->inp[0] && t->inp[1]  \
			&& t->inp[i] == '!'	&& t->inp[i + 1] == '!' && ++x)
			expand(t, i, 1, 2);
		else if (t->inp[0] && t->inp[1] && t->inp [2] \
			&& t->inp[i] == '!'	&& t->inp[i + 1] == '-' && ft_isdigit(t->inp[i + 2]) && ++x)
		{
			int j = i + 2;
			int len = 1;
			int digit = t->inp[j++] - 48;;
			while (ft_isdigit(t->inp[j]))
			{
				digit *= 10;
				digit += t->inp[j++] - 48;
				len++;
			}
			expand(t, i, digit, len + 2);
		}
	}
	if (x && ++t->total_row)
		ft_printf("\n%s", t->inp);
}

/*
 * It's called at the end of the main loop, and it handles the newline
 * character, the history, and the
 * input copy
 *
 * @param t the term struct
 */
void	ft_end_cycle(t_term *t)
{
	ft_history_expantion(t);
	if (t->bytes)
	{
		ft_memcpy(t->history_buff, t->inp, (unsigned long)t->bytes);
		ft_nl_removal(t);
		ft_history_add_command(t, t->history_buff);
	}
	ft_memdel((void **)&t->nl_addr);
	if (t->input_cpy)
		ft_strdel(&t->input_cpy);
}
