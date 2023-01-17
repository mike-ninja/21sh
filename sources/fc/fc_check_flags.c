/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_check_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:20:17 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/17 12:44:57 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

//add to libft
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

//add to libft
/* static char	*ft_strupdate(char *s1, const char *s2)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	if (!ret)
		return (NULL);
	ft_strdel(&s1);
	return (ret);
} */

static int	fc_s_flag(t_session *sesh, char ***cmd)
{
	if (*(cmd) && (*cmd)[1] && !(*cmd)[2])
	{
		ft_strdel(&sesh->term->history_arr[sesh->term->history_size - 1]);
		sesh->term->history_arr[sesh->term->history_size - 1] = \
		ft_strdup(sesh->term->history_arr[sesh->term->history_size - 2]);
		ft_freeda((void ***)cmd, calc_chptr(*cmd));
		ft_putendl(sesh->term->history_arr[sesh->term->history_size - 2]);
		*cmd = \
		ft_strsplit(sesh->term->history_arr[sesh->term->history_size - 2], ' ');
		if (!*cmd)
			fc_print_error(3);
		return (1);
	}
	else if (ft_strchr((*cmd)[2], '='))
	{
		int i;

		i = 0;
		char *change_to = ft_strchr((*cmd)[2], '=') + 1;
		//if null ??
		char *needle = ft_strsub((*cmd)[2], 0, ft_strchr((*cmd)[2], '=') - (*cmd)[2]);
		//free heystack

		//remove fc cmd
		ft_freeda((void ***)cmd, calc_chptr(*cmd));
		*cmd = \
		ft_strsplit(sesh->term->history_arr[sesh->term->history_size - i - 2], ' ');
		if (!*cmd)
			fc_print_error(3);
		while ((*cmd)[i])
		{
			while (ft_strstr((*cmd)[i], needle))
			{
				char	*begin;
				char	*end;

				begin = ft_strsub((*cmd)[i], 0, ft_strstr((*cmd)[i], needle) - (*cmd)[i]);
				end = ft_strsub((*cmd)[i], ft_strstr((*cmd)[i], needle) - (*cmd)[i] + ft_strlen(needle), ft_strlen((*cmd)[i]) - ft_strlen(needle));
				(*cmd)[i] = ft_strjoin_three(begin, change_to, end);
				ft_strdel(&begin);
				ft_strdel(&end);
			}
			i++;
		}
		ft_strdel(&needle);

		//update history
		/* ft_strdel(&sesh->term->history_arr[sesh->term->history_size - i - 1]);
		char *new_hist;
		for (int i = 0; (*cmd)[i]; i++)
		{
			ft_printf("%s ", (*cmd)[i]);
			new_hist = ft_strupdate(new_hist, (*cmd)[i]);
		}
		sesh->term->history_arr[sesh->term->history_size - i - 1] = new_hist; */


		ft_putchar('\n');
		/* char *ptr = ft_strstr(sesh->term->history_arr[sesh->term->history_size - i - 2], needle);
		if (ptr)
		{
			ft_printf("ptr: %s\n", ptr);
			ft_printf("change_to: %s\n", change_to);
			ft_printf("needle: %s\n", needle);
			ft_printf("history last: %s\n", sesh->term->history_arr[sesh->term->history_size - i - 2]);
			// char *str =
			// char *new = (char *)ft_memmove(ptr, change, ft_strlen(change));
			// char *new = (char *)ft_memmove(, change, ft_strlen(change));
		} */
		return (1);
	}
	return (0);
}

static int	fc_list_flag(t_session *sesh, char ***cmd) // fix for empy history? fc -l in fist line prints it out if its empty
{
	int i;

	if (sesh->term->history_size > FC_LEN)
		i = sesh->term->history_size - FC_LEN;
	else
		i = -1;
	if (!ft_strchr((*cmd)[1], 'n') && !ft_strchr((*cmd)[1], 'r'))
		while (sesh->term->history_arr[++i + 1])
			ft_printf("%-8d %s\n", i + 1, sesh->term->history_arr[i]);
	else if (ft_strchr((*cmd)[1], 'n') && !ft_strchr((*cmd)[1], 'r'))
		while (sesh->term->history_arr[++i + 1])
			ft_printf("\t %s\n", sesh->term->history_arr[i]);
	if (sesh->term->history_size > FC_LEN)
		i += FC_LEN;
	else
		i = sesh->term->history_size;
	if (ft_strchr((*cmd)[1], 'r') && !ft_strchr((*cmd)[1], 'n'))
		while (--i && i > (int)sesh->term->history_size - FC_LEN)
			ft_printf("%-8d %s\n", i, sesh->term->history_arr[i - 1]);
	else if (ft_strchr((*cmd)[1], 'r') && ft_strchr((*cmd)[1], 'n'))
		while (--i && i > (int)sesh->term->history_size - FC_LEN)
			ft_printf("\t %s\n", sesh->term->history_arr[i - 1]);
	return (0);
}

static int	loop_flags(t_session *sesh, char ***cmd)
{
	int i;

	i = 1;
	while ((*cmd)[1][i])
	{
		if ((*cmd)[1][i] == 's')
			return (fc_s_flag(sesh, cmd));
		else
			return (fc_list_flag(sesh, cmd));
	}
	return (1);
}

int	fc_check_flags(t_session *sesh, char ***cmd)
{
	int i;

	if (*cmd && ft_strnequ((*cmd)[1], "-", 1))
	{
		i = 1;
		while ((*cmd)[1][i])
		{
			if ((*cmd)[1][i] != 's' && (*cmd)[1][i] != 'l' && (*cmd)[1][i] != 'n' && (*cmd)[1][i] != 'r')
			{
				ft_putendl_fd("42sh: fc: invalid option\nfc: usage: fc [-e ename] [-lnr] [first] [last] or fc -s [pat=rep] [command]", 2);
				return (0);
			}
			i++;
		}
	}
	return (loop_flags(sesh, cmd));
}
