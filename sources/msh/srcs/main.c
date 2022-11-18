/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 06:21:44 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/20 11:53:29 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_input(t_session *sesh, char *line)
{
	get_args(sesh, &line);
	if (*sesh->tok->arg)
	{
		cycle(sesh, START);
		built_ins(sesh);
		if (sesh->result == 1)
		{
			if (ft_strcmp(*sesh->tok->arg, "exit") == 0)
				ft_exit(sesh, "exit", RESET);
			if (system_call(sesh) == ERROR)
				return (ERROR);
			if (sesh->result < 0)
			{
				error_message(sesh);
				return (ERROR);
			}
		}
		else if (sesh->result != RESET)
			error_message(sesh);
	}
	cycle(sesh, END);
	sesh->result = RESET;
	return (sesh->result);
}

static void	init_tokens(t_session *sesh)
{
	sesh->tok->arg = NULL;
	sesh->tok->tok = NULL;
}

static void	session_init(t_session *sesh)
{
	sesh->result = RESET;
	sesh->tm_en = NULL;
	sesh->tok = (t_tokens *)ft_memalloc(sizeof(t_tokens));
	init_tokens(sesh);
	sesh->env = env_init();
	sesh->env = mandatory_env(sesh);
}

int	main(void)
{
	t_session	sesh[1];
	char		line[BUFF_SIZE];

	header_print();
	session_init(sesh);
	while (1)
	{
		ft_printf(PROMPT);
		ft_termcaps(line);
		if (*line)
			if (execute_input(sesh, line) == ERROR)
				return (ERROR);
	}
	return (RESET);
}
