/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_arg_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 21:59:23 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/02 22:25:42 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*									MINISHELL							*/
static int	arg_qty_loop(char *cmd)
{
	int len;

	len = 0;
	while (cmd)
	{
		if (*cmd == '"')
		{
			++cmd;
			ft_strsep(&cmd, "\"");
		}
		else if (*cmd == '\'')
		{
			++cmd;
			ft_strsep(&cmd, "\'");
		}
		else
			ft_strsep(&cmd, " ");
		cmd = ft_skip_space(cmd);
		len++;
	}
	return (len);
}

static void	collect_args_loop(char **array, char *cmd)
{
	int i;

	i = 0;
	while (cmd)
	{
		if (*cmd == '\"')
		{
			++cmd;
			array[i++] = ft_strdup(ft_strsep(&cmd, "\""));
		}
		else if (*cmd == '\'')
		{
			++cmd;
			array[i++] = ft_strdup(ft_strsep(&cmd, "\'"));
		}
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

	len = arg_qty(ft_strdup(cmd));
	array = (char **)ft_memalloc(sizeof(char *) * (len + 1));
	cmd = ft_skip_space(cmd);
	collect_args_loop(array, cmd);
	ft_strdel(&cmd);
	return (array);
}

/*									MINISHELL							*/

// static char **make_arg_array(char *cmd) // promlem here
// {
// 	int argc;
// 	int i;
// 	char **args;

// 	increment_whitespace(&cmd);
// 	argc = ft_calc_chr(cmd, ' ') + 1;
// 	args = ft_memalloc(sizeof(*args) * (argc + 1));
// 	i = 0;
// 	while (*cmd && i < argc)
// 	{
// 		increment_whitespace(&cmd);
// 		args[i] = cmd;
// 		increment_not_whitespace(&cmd);
// 		*cmd = '\0';
// 		// ft_putendl(args[i]);
// 		++cmd;
// 		++i;
// 	}
// 	//	null_terminate_strings(args);
// 	return (args);
// }