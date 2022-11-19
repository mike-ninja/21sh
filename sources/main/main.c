/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 09:30:04 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/19 14:20:38 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

// Setup the attributes
// run the keyboard function
// t->inp contains the input that will go through lexer
// run the lexer **
// TOkenizing

// banner_print();
// ft_keyboard(&t);
// ft_printf(t.inp);
// uninit_keyboard(&t);
// input array here
// initialise keyboard
// get the input and perhaps copy it to a new string?
// lexer
// parser
// tree generation?

// static void uninit_keyboard(t_term *t)
// {
// 	ft_memdel((void **)&t->nl_addr);
// }

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
 * It disables raw mode by setting the terminal attributes to the original terminal attributes
 *
 * @param orig_termios The original terminal attributes.
 */
static void	disable_raw_mode(struct termios orig_termios)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
	ft_run_capability("te");
}

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
	int				stat;
	t_term			term;
	struct termios	orig_termios;

	stat = 1;
	ft_getent();
	orig_termios = enable_raw_mode();
	banner_print();
	while (stat)
	{
		ft_keyboard(&term);
		if (!ft_strcmp(term.inp, "exit"))
			stat = 0;
		else
		{
			ft_putstr(term.inp);
			ft_putchar('\n');
		}
	}
	disable_raw_mode(orig_termios);
	return (0);
	// initialise the raw mode
}
