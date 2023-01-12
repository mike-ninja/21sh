/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion_excla.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:57:35 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/12 14:39:02 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

extern t_term	*g_t;

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

static char	**ft_special_ch_split(char *str)
{
	int		i;
	int		j;
	char	**ret;

	j = 0;
	ret = (char **)ft_memalloc(sizeof(char *) * \
	(ft_special_ch_split_len(str) + 1));
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

static void	catinate_expansion(char **splits, char **buff)
{
	char	*tofree;

	tofree = NULL;
	if (**splits == '!' && ft_strlen(*splits) > 1)
	{
		if (!*buff)
			// *buff = ft_find_history(sesh, *splits);
			*buff = ft_strdup(g_t->history_arr[g_t->history_size]);
		else
		{
			// tofree = ft_find_history(sesh, *splits);
			tofree = ft_strdup(g_t->history_arr[g_t->history_size]);
			*buff = strjoin_head(*buff, tofree);
			ft_strdel(&tofree);
		}
	}
	else
	{
		if (!*buff)
			*buff = ft_strdup(*splits);
		else
			*buff = strjoin_head(*buff, *splits);
	}
	ft_strdel(splits);
}


char	*ft_expansion_excla(char *str, int i)
{
	char	*buff;
	char	**split_excla;

	buff = NULL;
	split_excla = ft_special_ch_split(str);
	/* for (int x = 0; split_excla[x]; x++)
		ft_printf("split_excla[%d] = %s\n", x, split_excla[x]); */
	i = -1;
	while (split_excla[++i])
		catinate_expansion(&split_excla[i], &buff);
	ft_memdel((void **)&split_excla);
	return (buff);
}
