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
static char	*ft_strupdate(char *s1, const char *s2)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	if (!ret)
		return (NULL);
	ft_strdel(&s1);
	return (ret);
}

static void fc_use_last_match(t_session *sesh, char ***cmd, int y)
{
	ft_freeda((void ***)cmd, calc_chptr(*cmd));
	*cmd = \
	ft_strsplit(sesh->term->history_arr[y], ' ');
	if (!*cmd)
		fc_print_error(3);

	ft_strdel(&sesh->term->history_arr[sesh->term->history_size - 1]);
	char *new_hist;
	new_hist = ft_strnew(0);
	for (int i = 0; (*cmd)[i]; i++)
	{
		ft_printf("%s ", (*cmd)[i]);
		new_hist = ft_strupdate(new_hist, (*cmd)[i]);
		if ((*cmd)[i + 1])
			new_hist = ft_strupdate(new_hist, " ");
	}
	write(1, "\n", 1);
	sesh->term->history_arr[sesh->term->history_size - 1] = new_hist;
}

static int	find_matching(t_session *sesh, char *str, char ***cmd)
{
	int		y;
	int		x;
	int		len;

	y = sesh->term->history_size - 1;
	len = ft_strlen(str);
	while (y > 0)
	{
		x = 0;
		while (sesh->term->history_arr[y][x] && str[x] && sesh->term->history_arr[y][x] == str[x])
			x++;
		if (x == len)
		{
			fc_use_last_match(sesh, cmd, y);
			break ;
		}
		y--;
	}
	if (y == 0)
		return (fc_print_error(5));
	return (1);
}

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
	else if (ft_strchr((*cmd)[2], '=')) //make it into a while loop that takes all the '=' in every arg
	{
		int i;

		char *change_to = ft_strdup(ft_strchr((*cmd)[2], '=') + 1);
		char *needle = ft_strsub((*cmd)[2], 0, ft_strchr((*cmd)[2], '=') - (*cmd)[2]);
		//remove fc cmd
		ft_freeda((void ***)cmd, calc_chptr(*cmd));
		*cmd = \
		ft_strsplit(sesh->term->history_arr[sesh->term->history_size - 2], ' ');
		if (!*cmd)
			fc_print_error(3);
		i = 0;
		while ((*cmd)[i])
		{
			while (ft_strstr((*cmd)[i], needle))
			{
				char	*begin;
				char	*end;

				begin = ft_strsub((*cmd)[i], 0, ft_strstr((*cmd)[i], needle) - (*cmd)[i]);
				end = ft_strsub((*cmd)[i], ft_strstr((*cmd)[i], needle) - (*cmd)[i] + ft_strlen(needle), ft_strlen((*cmd)[i]) - ft_strlen(needle) - ft_strlen(begin));
				ft_strdel(&(*cmd)[i]);
				(*cmd)[i] = ft_strjoin_three(begin, change_to, end);
				ft_strdel(&begin);
				ft_strdel(&end);
			}
			i++;
		}
		ft_strdel(&needle);
		ft_strdel(&change_to);
		//update history
		ft_strdel(&sesh->term->history_arr[sesh->term->history_size - 1]);
		char *new_hist;
		new_hist = ft_strnew(0);
		for (int i = 0; (*cmd)[i]; i++)
		{
			ft_printf("%s ", (*cmd)[i]);
			new_hist = ft_strupdate(new_hist, (*cmd)[i]);
			if ((*cmd)[i + 1])
				new_hist = ft_strupdate(new_hist, " ");
		}
		sesh->term->history_arr[sesh->term->history_size - 1] = new_hist;

		ft_putchar('\n');
		return (1);
	}
	else if (!ft_strchr((*cmd)[2], '='))
	{
		find_matching(sesh, (*cmd)[2], cmd);
		return (1);
	}
	return (0);
}

static int	null_check_first(t_session *sesh, char *cmd)
{
	int start;

	if (ft_atoi(cmd) == 0)
	{
		start = sesh->term->history_size - 3;
		sesh->term->history_size -= 1;
	}
	else
		start = ft_atoi(cmd) - 2;
	if (start < -1)
	{
		start = sesh->term->history_size + start;
		if (start < 0)
			start = -1;
	}
	return (start);
}

static int	null_check_last(t_session *sesh, char *cmd)
{
	int last;

	if (ft_atoi(cmd) == 0)
		last = sesh->term->history_size;
	else
		last = ft_atoi(cmd) + 1;
	if (last <= 0)
		last = sesh->term->history_size;
	return (last);
}

static int	get_start(t_session *sesh, char ***cmd)
{
	int start;

	if ((*cmd)[0] && (*cmd)[1] && (*cmd)[2] && !(*cmd)[3])
		start = null_check_first(sesh, (*cmd)[2]);
	else if ((*cmd)[0] && (*cmd)[1] && (*cmd)[2] && (*cmd)[3])
	{
		start = null_check_first(sesh, (*cmd)[2]);
		sesh->term->history_size = null_check_last(sesh, (*cmd)[3]);
	}
	else if (sesh->term->history_size > FC_LEN)
		start = sesh->term->history_size - FC_LEN;
	else
		start = -1;
	return (start);
}

static void print_ell_only(t_session *sesh, int start)
{
	while (++start < (int)sesh->term->history_size - 1)
			ft_printf("%-8d %s\n", start + 1, sesh->term->history_arr[start]);
}

static void print_n_ell(t_session *sesh, int start)
{
	while (++start < (int)sesh->term->history_size - 1)
		ft_printf("\t %s\n", sesh->term->history_arr[start]);
}

static void print_r_ell(t_session *sesh, int start)
{
	while (--start && start > (int)sesh->term->history_size - FC_LEN)
		ft_printf("%-8d %s\n", start, sesh->term->history_arr[start - 1]);
}

static void print_nr_ell(t_session *sesh, int start)
{
	while (--start && start > (int)sesh->term->history_size - FC_LEN)
			ft_printf("\t %s\n", sesh->term->history_arr[start - 1]);
}

//add [fist] [last] option to the call
static int	fc_list_flag(t_session *sesh, char ***cmd) // fix for empy history? fc -l in fist line prints it out if its empty
{
	int 	start;
	size_t	hold;

	hold = sesh->term->history_size;
	start = get_start(sesh, cmd);
	if (!ft_strchr((*cmd)[1], 'n') && !ft_strchr((*cmd)[1], 'r'))
		print_ell_only(sesh, start);
	else if (ft_strchr((*cmd)[1], 'n') && !ft_strchr((*cmd)[1], 'r'))
		print_n_ell(sesh, start);
	if (sesh->term->history_size > FC_LEN)
		start += FC_LEN;
	else
		start = sesh->term->history_size;
	if (ft_strchr((*cmd)[1], 'r') && !ft_strchr((*cmd)[1], 'n'))
		print_r_ell(sesh, start);
	else if (ft_strchr((*cmd)[1], 'r') && ft_strchr((*cmd)[1], 'n'))
		print_nr_ell(sesh, start);
	if (hold != sesh->term->history_size)
		sesh->term->history_size = hold;
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
