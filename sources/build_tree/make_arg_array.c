/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_arg_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 21:59:23 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/16 15:16:46 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*									MINISHELL							*/
// static int	arg_qty_loop(char *cmd)
// {
// 	int	len;

// 	len = 0;
// 	while (cmd)
// 	{
// 		if (*cmd == '"')
// 		{
// 			++cmd;
// 			ft_strsep(&cmd, "\"");
// 		}
// 		else if (*cmd == '\'')
// 		{
// 			++cmd;
// 			ft_strsep(&cmd, "\'");
// 		}
// 		else
// 			ft_strsep(&cmd, " ");
// 		cmd = ft_skip_space(cmd);
// 		len++;
// 	}
// 	return (len);
// }
static int	arg_qty_loop(char *cmd)
{
	int	len;

	len = 0;
	while (cmd)
	{
		if (*cmd == '"')
		{
			ft_strsep(&cmd, "\"");
			if (ft_isspace(*(cmd + 1)) || *cmd == '\0')
				len++;
			++cmd;
		}
		else if (*cmd == '\'')
		{
			ft_strsep(&cmd, "\'");
			if (ft_isspace(*(cmd + 1)) || *cmd == '\0')
				len++;
			++cmd;
		}
		else
		{
			ft_strsep(&cmd, " ");
			len++;
		}
		cmd = ft_skip_space(cmd);
		
	}
	return (len);
}



static int	find_closing_quote(char **cmd, char c)
{
	int	i;

	i = 1;
	while ((*cmd)[i] && ((*cmd)[i] != c || !ft_isspace(*cmd[i + 1])))
		i++;
	if ((*cmd)[i] == c)
		i++;
	*cmd = *cmd + i;
	return (i);
}

static void	collect_args_loop(char **array, char *cmd)
{
	int		i;

	i = 0;
	while (cmd)
	{
		if (*cmd == '\"')
			array[i++] = ft_strsub(cmd, 0, find_closing_quote(&cmd, '\"'));
		else if (*cmd == '\'')
			array[i++] = ft_strsub(cmd, 0, find_closing_quote(&cmd, '\''));
		else
			array[i++] = ft_strdup(ft_strsep(&cmd, " "));
		cmd = ft_skip_space(cmd);
	}
	array[i] = NULL;
}

static int	arg_qty(char *cmd)
{
	int		len;
	char	*tofree;

	tofree = cmd;
	cmd = ft_skip_space(cmd);
	len = arg_qty_loop(cmd);
	ft_strdel(&tofree);
	return (len);
}

char	**make_arg_array(char *cmd)
{
	int		len;
	char	**array;

	// ft_printf("cmd = %s\n", cmd);
	len = arg_qty(ft_strdup(cmd));
	array = (char **)ft_memalloc(sizeof(char *) * (len + 1));
	cmd = ft_skip_space(cmd);
	collect_args_loop(array, cmd);
	return (array);
}
