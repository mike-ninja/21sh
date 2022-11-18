/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 11:05:20 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/19 12:45:28 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	arg_clean(t_tokens *toks)
{
	int	i;

	i = -1;
	while (toks->arg[++i])
		ft_strdel(&toks->arg[i]);
	ft_memdel((void **)&toks->arg);
	ft_memdel((void **)&toks->tok);
}

void	env_clean(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		ft_strdel(&env[i]);
	ft_memdel((void **)&env);
}

void	ft_exit(t_session *sesh, char *message, int status)
{
	if (message)
		ft_printf("-minishell: %s: %s\n", *sesh->tok->arg, message);
	env_clean(sesh->env);
	arg_clean(sesh->tok);
	ft_memdel((void **)&sesh->tok);
	exit(status);
}
