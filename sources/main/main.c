/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 09:30:04 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/21 13:31:32 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

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
	ft_run_capability("ti");
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
	ft_run_capability("te");
}

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

int	main(void)
{
	t_term			term;
	char			*line;
	int				status;
	struct termios	orig_termios;
	t_token			*tokens;

	tokens = (t_token *)ft_memalloc(sizeof(*tokens) * 2);
	status = 1;
	line = NULL;
	ft_getent();
	orig_termios = enable_raw_mode();
	banner_print();
	while (status)
	{
		ft_keyboard(&term);
		if (!ft_strcmp(term.inp, "exit"))
			status = 0;
		else
		{
			line = ft_lexer(term.inp);
			tokens = chop_line(line, tokens, 2);
			ft_putstr(line);
			ft_strdel(&line);
			ft_putchar('\n');
		}
	}
	disable_raw_mode(orig_termios);
	return (0);
}
