/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 09:30:04 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/02 20:17:45 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/**
 * It gets the terminal type from the environment, and then uses the termcap
 * library to get the terminal capabilities
 *
 * @return The number of lines in the terminal.
 */
static int ft_getent(void)
{
	char	*termtype;
	char	term_buffer[2048];
	int		status;

	termtype = getenv("TERM");
	if (termtype == NULL)
	{
		printf("could not get the TERM env\n");
		exit(1);
	}
	status = tgetent(term_buffer, termtype);
	if (status < 0)
	{
		printf("could not access the termcap data base\n");
		exit(1);
	}
	else if (status == 0)
	{
		printf("could not find the termtype\n");
		exit(1);
	}
	return (status);
}

/**
 * It puts the terminal into raw mode
 *
 * @return The original terminal settings.
 */
static struct termios	enable_raw_mode(void)
{
	struct termios	orig_termios;
	struct termios	raw;

	if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
	{
		write(2, "error tcgetattr\n", 16);
		exit(1);
	}
	raw = orig_termios;
	raw.c_lflag &= ~(ICANON | ECHO | IEXTEN | ISIG);
	raw.c_iflag &= ~(IXON | BRKINT);
	raw.c_cc[VMIN] = 1;
	raw.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
	{
		write(2, "error tcsetattr\n", 16);
		exit(1);
	}
	ft_run_capability("cl");
	return (orig_termios);
}

/**
 * It disables raw mode by setting the terminal attributes to the original
 * terminal attributes
 *
 * @param orig_termios The original terminal attributes.
 */
static void	disable_raw_mode(struct termios orig_termios)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

int	main(int argc, char **argv)
{
	t_term			term;
	char			*line;
	int				status;
	t_session		sesh[1];
	struct termios	orig_termios;

	status = 1;
	line = NULL;
	ft_getent();
	orig_termios = enable_raw_mode();
	banner_print();
	ft_session_init(sesh);
	while (status)
	{
		ft_keyboard(&term);
		if (!ft_strcmp(term.inp, "exit"))
		{
			ft_endcycle(sesh);
			status = 0;
		}
		else
		{
			sesh->tokens = chop_line(term.inp, sesh->tokens, 1);
			sesh->head = build_tree(sesh->tokens);
			if (ft_builtins(sesh) == 1)
			{
				if (sesh->head && sesh->head->type == CMD && fork_wrap() == 0)
					execute_bin(((t_cmdnode *)sesh->head)->cmd, &sesh->env);
				else if (sesh->head && sesh->head->type != CMD)
					exec_tree(sesh->head, &sesh->env);
			}
		//	wait (0);
			/*		debugging		*/
//				int i_args = -1;
//				while (sesh->tokens[++i_args].token)
//				{
//					ft_putstr(sesh->tokens[i_args].value);
//					if (sesh->tokens[i_args + 1].token)
//						ft_putchar(' ');
//				}
//				ft_putchar('\n');
			/*		debugging		*/
			ft_strdel(&line);
		}
		ft_endcycle(sesh);
	}
	disable_raw_mode(orig_termios);
	return (0);
}
