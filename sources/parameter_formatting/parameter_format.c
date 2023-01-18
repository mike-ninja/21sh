/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:40:05 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/18 12:57:43 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	check_syntax(char *cmd)
{
	int	i;
	int	valid;

	i = 0;
	valid = -1;
	if (ft_strnequ(cmd, "${", 2))
	{
		i += 2;
		valid = 0;
		if (cmd[i] && ft_isalpha(cmd[i]))
		{
			while (cmd[i])
			{
				if (cmd[i] == ':')
					valid += 1;
				else if (cmd[i] == '}')
					valid += 1;
				i++;
			}
				
		}
		if (valid == 2)
			return (1);
		else
			ft_printf("no %d\n", valid);
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
		if(str[i] == '\0')
			break ;
		new[k++] = str[i++];
	}
	return (new);
}

void add_var_to_list(t_session *sesh, char *var, char *subst)
{
	int	i;

	i = 0;
	while (sesh->intr_vars[i])
		i++;
	sesh->intr_vars[i] = ft_strjoin(var + 1, subst);
}

int	is_in_var_or_env(t_session *sesh, char *var)
{
	int i;
	int	var_len;
	char	*key;

	i = -1;
	
	key = ft_strjoin(var, "=");
	var_len = ft_strlen(key);
	ft_printf("key %s\n", key);
	while(sesh->intr_vars[++i])
	{
		if (ft_strncmp(sesh->intr_vars[i], key, var_len) == 0
			&& sesh->intr_vars[i][var_len - 1] == '=')
			return (1);
	}
	i = -1;
	while(sesh->env[++i])
	{
		if (ft_strncmp(sesh->env[i], key, var_len) == 0
			&& sesh->env[i][var_len - 1] == '=')
			return (1);
	}
	return (0);
}

char	*subst_param(t_session *sesh, char *var, char *subst, int format)
{
	char	*expanded;
	char	**temp;

	expanded = NULL;
	temp = (char **)ft_memalloc(sizeof(char *) * 2);
	temp[0] = ft_expansion_dollar(sesh, var);
	temp[1] = NULL;
	if (format == 0)
	{
		ft_printf("[%s]\n", temp[0]);
		if (!temp[0])
			expanded = ft_strdup(subst + 1);
		else
			expanded = ft_strdup(var);
		return (expanded);
	}
	else if (format == 1)
	{
		ft_printf("[%s]", var);
		if (!*temp[0])
		{
			expanded = ft_strdup(subst + 1);
			ft_strdel(&temp[0]);
			temp[0] = ft_strjoin(var + 1, subst);
			ft_printf("temp [%s]\n", temp[0]);
			add_var(sesh, temp);
			//add_var_to_list(sesh, var, subst);
		}
		else
			expanded = ft_strdup(temp[0]);

	}
	else if (format == 2)
	{
		ft_printf("questionmark[%s]\n", var);
		if (!*temp[0] && subst[1])
			ft_printf("21sh: %s: %s\n", var + 1, subst + 1);
		else if (!*temp[0] && !subst[1])
			ft_printf("21sh: %s: parameter null or unset\n", var + 1);
		else
			expanded = ft_strdup(temp[0]);

	}
	else if (format == 3)
	{
		ft_printf("plus sign[%s] %s\n", var, subst);
		if (temp[0])
			expanded = ft_strdup(subst + 1);
		ft_printf("expanded[%s]", expanded);
	}
	return (expanded);
}

int	format_mode(char *var)
{
	int		format;
	char	subst_mode;

	format = -1;
	subst_mode = var[0];
	ft_printf("subst mode %c\n", subst_mode);
	if (subst_mode == '-')
		format = 0;
	else if (subst_mode == '=')
		format = 1;
	else if (subst_mode == '?')
		format = 2;
	else if (subst_mode == '+')
		format = 3;
	return (format);
}

int	param_format(t_session *sesh, char **cmd)
{
	int		i;
	char	*expanded;
	char	*strip;
	char	*var;
	char	*subs;
	int		format;

	i = -1;
	subs = NULL;
	expanded = NULL;
	while (cmd[++i])
	{
		if (check_syntax(cmd[i]))
		{
			strip = remove_braces(cmd[i]);
			subs = ft_strdup(ft_strchr(strip, ':') + 1);
			var = ft_strndup(strip, ft_strlen(strip) - ft_strlen(subs) - 1);
			format = format_mode(subs);
			ft_printf("stripped %s variable %s format %d\n", strip, subs, format);
			if (format != -1)
				expanded = subst_param(sesh, var, subs, format);
			if (expanded == NULL)
			{
				return (-1);
			}
			else if (expanded[0] == '$')
				expanded = ft_expansion_dollar(sesh, var);
			ft_strdel(&cmd[i]);
			cmd[i] = ft_strdup(expanded);
			ft_strdel(&var);
			ft_strdel(&subs);
			ft_printf("Expanded %s\n", cmd[i]);
		}
	}
	return (0);
}
