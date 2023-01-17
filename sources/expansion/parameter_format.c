/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:40:05 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/17 16:03:25 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	check_syntax(char *cmd)
{
	int	i;
	int	open;

	i = 0;
	open = -1;
	if (ft_strnequ(cmd, "${", 2))
	{
		i += 2;
		open = 1;
		if (cmd[i] && ft_isalpha(cmd[i]))
		{
			while (cmd[i])
				if (cmd[i++] == '}')
					open = 0;
		}
		if (open == 0)
			return (1);
		else
			ft_printf("no\n");
	}
	return (0);
}

char	*remove_braces(char *str)
{
	char	*new;
	int		i;
	int		k;

	k = 0;
	i = 0;
	new = ft_strnew(ft_strlen(str));
	while (str[i])
	{
		if (str[i] == '{' || str[i] == '}')
			i++;
		new[k++] = str[i++];
	}
	return (new);
}

char	*subst_param(t_session *sesh, char *var, char *subst, int format)
{
	char	*expanded;

	expanded = NULL;
	var = ft_expansion_dollar(sesh, var);
	if (format == 0)
	{
		ft_printf("[%s]", var);
		if (!*var)
			expanded = ft_strdup(subst + 1);
		else
			expanded = ft_strdup(var);
		return (expanded);
	}
	else if (format == 1)
	{
		ft_printf("[%s]", var);
		if (!*var)
			expanded = ft_strdup(subst + 1);
		else
			expanded = ft_strdup(var);
		return (expanded);
	}
	return (expanded);
}

int	format_mode(char *var)
{
	int		format;
	char	subst_mode;

	format = -1;
	subst_mode = var[0];
	ft_printf("%c\n", subst_mode);
	if (subst_mode == '-')
		format = 0;
	else if (subst_mode == '+')
		format = 1;
	else if (subst_mode == '=')
		format = 2;
	else if (subst_mode == '?')
		format = 3;
	return (format);
}

void	param_format(t_session *sesh, char **cmd)
{
	int		i;
	char	*expanded;
	char	*strip;
	char	*var;
	char	*subs;
	int		format;

	i = -1;
	while (cmd[++i])
	{
		if (check_syntax(cmd[i]))
		{
			strip = remove_braces(cmd[i]);
			subs = ft_strdup(ft_strchr(strip, ':') + 1);
			var = ft_strndup(strip, ft_strlen(strip) - ft_strlen(subs) - 1);
			format = format_mode(subs);
			ft_printf("stripped %s variable %s format %d\n", var, subs, format);
			if (format != -1)
				expanded = subst_param(sesh, var, subs, format);
			else
				expanded = ft_expansion_dollar(sesh, strip);
			ft_printf("Expanded %s\n", expanded);
			ft_strdel(&cmd[i]);
			cmd[i] = ft_strdup(expanded);
			ft_strdel(&strip);
		}
	}
}
