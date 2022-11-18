/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:42:38 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/19 13:01:21 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_arg(t_session *sesh, char **arg)
{
	int		i;
	int		len;
	char	**new_arg;
	bool	*tokens;

	len = array_len(arg, END);
	new_arg = (char **)malloc(sizeof(char *) * (len + 1));
	if (len)
		tokens = (bool *)ft_memalloc(sizeof(bool) * (len));
	if (!new_arg || (!sesh->tok->tok && len))
		ft_exit_no_mem(1);
	i = -1;
	while (arg[++i])
	{
		new_arg[i] = ft_strdup(arg[i]);
		tokens[i] = sesh->tok->tok[i];
	}
	new_arg[i] = NULL;
	arg_clean(sesh->tok);
	sesh->tok->arg = new_arg;
	sesh->tok->tok = tokens;
}

static int	tmp_env_qty(char **arg)
{
	int	len;

	len = 0;
	while (arg[len] && ft_strchr(arg[len], '=') && *arg[len] != '=')
		len++;
	return (len);
}

static void	key_str(t_session *sesh, char *arg, int *j)
{
	char	*sep;
	char	*tofree;

	sep = NULL;
	tofree = NULL;
	sep = ft_strdup(arg);
	append_env(sesh, &arg);
	tofree = sep;
	sesh->tm_en[j[0]++] = ft_strdup(ft_strsep(&sep, "="));
	ft_strdel(&tofree);
}

static int	set_tmp_env(t_session *sesh, int i)
{
	int		j;
	char	*replaced;

	j = 0;
	sesh->tm_en = (char **)malloc(sizeof(char *)
			* (tmp_env_qty(&sesh->tok->arg[i]) + 1));
	if (!sesh->tm_en)
		ft_exit_no_mem(1);
	while (sesh->tok->arg[i] && ft_strchr(sesh->tok->arg[i], '=')
		&& *sesh->tok->arg[i] != '=')
	{
		if (!replace_value(sesh, ft_strdup(sesh->tok->arg[i]), &replaced))
			key_str(sesh, sesh->tok->arg[i], &j);
		else
			sesh->tm_en[j++] = replaced;
		i++;
	}
	sesh->tm_en[j] = NULL;
	return (i);
}

int	cmd_env(t_session *sesh)
{
	int		i;
	char	**env;

	i = 1;
	if (sesh->tok->arg[i] && ft_strchr(sesh->tok->arg[i], '='))
		i = set_tmp_env(sesh, i);
	if (sesh->tok->arg[i])
	{
		sesh->result = ERROR;
		update_arg(sesh, &sesh->tok->arg[i]);
		return (ERROR);
	}
	env = sesh->env;
	while (*env)
	{
		ft_printf("%s\n", *env);
		env++;
	}
	return (RESET);
}
