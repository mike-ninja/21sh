/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyboard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:52:45 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/09 13:44:12 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * ECHO is a bitflag, defined as 00000000000000000000000000001000 in binary.
 * We use the bitwise-NOT operator (~) on this value to get
 * 11111111111111111111111111110111. We then bitwise-AND this value with the
 * flags field, which forces the fourth bit in the flags field to become 0,
 * and causes every other bit to retain its current value. Flipping bits like
 * this is common in C.
 * There is an ICANON flag that allows us to turn off canonical mode.
 * This means we will finally be reading input byte-by-byte,
 * instead of line-by-line.
 * Turning off IEXTEN also fixes Ctrl-O in macOS, whose terminal driver
 * is otherwise set to discard that control character.
 * IXON comes from <termios.h>. The I stands for “input flag” (which it is,
 * unlike the other I flags we’ve seen so far) and XON comes from the names
 * of the two control characters that Ctrl-S and Ctrl-Q produce: XOFF to pause
 * transmission and XON to resume transmission.
 * BRKINT this step probably won’t have any observable effect for you, because
 * these flags are either already turned off, or they don’t really apply to
 * modern terminal emulators. But at one time or another, switching them off
 * was considered (by someone) to be part of enabling “raw mode”, so we carry
 * on the tradition (of whoever that someone was) in our program.
 * If optional_actions is TCSAFLUSH, the change shall occur after all output
 * written to fildes is transmitted, and all input so far received but not
 * read shall be discarded before the change is made.
 */
// static struct termios	ft_init_raw(void)
// {
// 	struct termios	orig_termios;
// 	struct termios	raw;

// 	if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
// 	{
// 		write(2, "error tcgetattr\n", 16);
// 		exit(1);
// 	}
// 	raw = orig_termios;
// 	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN);
// 	raw.c_iflag &= ~(IXON | BRKINT);
// 	raw.c_cc[VMIN] = 1;
// 	raw.c_cc[VTIME] = 0;
// 	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
// 	{
// 		write(2, "error tcsetattr\n", 16);
// 		exit(1);
// 	}
// 	ft_run_capability("cl");
// 	return (orig_termios);
// }

/*
 * It disables raw mode by setting the terminal attributes to the original
 * terminal attributes
 *
 * @param orig_termios The original terminal attributes.
 */
// static void	ft_disable_raw_mode(struct termios orig_termios)
// {
// 	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
// }

/*
 * It gets the terminal type from the environment, and then uses the termcap
 * library to get the
 * terminal capabilities
 *
 * @return The number of lines in the terminal.
 */
// static int	ft_getent(void)
// {
// 	char	*termtype;
// 	char	term_buffer[2048];
// 	int		status;

// 	termtype = getenv("TERM");
// 	if (termtype == NULL)
// 	{
// 		printf("could not get the TERM env\n");
// 		exit(1);
// 	}
// 	status = tgetent(term_buffer, termtype);
// 	if (status < 0)
// 	{
// 		printf("could not access the termcap data base\n");
// 		exit(1);
// 	}
// 	else if (status == 0)
// 	{
// 		printf("could not find the termtype\n");
// 		exit(1);
// 	}
// 	return (status);
// }

/*
 * It initializes the terminal, reads input, and then cleans up
 *
 * @return The return value of the last command executed.
 */
// static int	ft_keyboard(void)
// {
// 	struct termios	orig_termios;
// 	t_term			t;

// 	ft_getent();
// 	orig_termios = ft_init_raw();
// 	ft_init(&t);
// 	ft_input_cycle(&t);
// 	if (t.nl_addr)
// 		ft_memdel((void **)&t.nl_addr);
// 	ft_history_write_to_file(&t);
// 	ft_disable_raw_mode(orig_termios);
// 	return (0);
// }

// int	main(void)
// {
// 	ft_keyboard();
// 	return (0);
// }

int	ft_keyboard(t_term *t)
{
	int	ret;

	ft_init(t);
	ret = ft_input_cycle(t);
	if (t->nl_addr)
		ft_memdel((void **)&t->nl_addr);
	if (!*t->inp)
		ft_putchar('\n');
	return (ret);
}

// int	main(void)
// {
// 	struct termios	orig_termios;
// 	t_term			t;
// 	int				status;

// 	status = 1;
// 	ft_getent();
// 	orig_termios = ft_init_raw();
// 	ft_history_get(&t);
// 	while (status)
// 	{
// 		if (ft_keyboard(&t) == 1 || ft_strcmp(t.inp, "exit") == 0)
// 			status = 0;
// 		else
// 			ft_putendl(t.inp);
// 	}
// 	ft_history_write_to_file(&t);
// 	ft_disable_raw_mode(orig_termios);
// }
