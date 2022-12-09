/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_cycle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:46:24 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/09 14:00:01 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It deletes the character
 * under the cursor if there is one, and if the cursor is at the end of a line
 * and the line is empty, it ends the current cycle and restarts it.
 *
 * @param t the term structure
 *
 * @return the value of the function ctrl_d.
 */
static int	ctrl_d(t_term *t)
{
	if (!t->bytes)
		return (-1);
	if (t->index < t->bytes)
		ft_delete(t);
	if (t->heredoc && !*t->nl_addr[t->c_row])
	{
		ft_putstr("21sh: warning: here-document at line ");
		ft_putnbr(t->c_row);
		ft_putstr(" delimited by end-of-file (wanted `EOF')");
		ft_end_cycle(t);
		ft_restart_cycle(t);
		return (1);
	}
	return (0);
}

/*
 * It handles backspaces and escape sequences
 *
 * @param t the t_term struct
 */
static void	ft_backspace_or_escape(t_term *t)
{
	if (t->ch == BACKSPACE && t->index)
		ft_backspace(t);
	if (t->ch == ESCAPE)
		ft_esc_parse(t);
}

/*
 * It inserts a character into the line, and if it's an enter, it checks if
 * the line is complete and if so, it ends the cycle
 *
 * @param t the structure containing all the information about the current line
 *
 * @return 1 or 0
 */
static int	ft_isprint_or_enter(t_term *t)
{
	if (ft_isprint(t->ch) || t->ch == ENTER)
		ft_insertion(t);
	if (t->ch == ENTER)
	{
		if ((!t->bslash && !(t->q_qty % 2) && !t->delim) \
			|| (t->delim && !ft_strcmp(t->nl_addr[t->c_row], t->delim)))
		{
			ft_end_cycle(t);
			return (1);
		}
		t->bslash = 0;
	}
	return (0);
}

static int	ctrl_d_exit(void)
{
	ft_putchar('\n');
	ft_putendl("exit");
	return (1);
}

/*
 * It reads input from the terminal, and if the input is a printable
 * character, it adds it to the current row, if the input is a backspace,
 * it deletes the last character from the current row, if the
 * input is an escape sequence, it calls the appropriate function,
 * and if the input is a control
 * character, it calls the appropriate function
 *
 * @param t the t_term struct
 */
int	ft_input_cycle(t_term *t)
{
	int		ctrl_d_ret;

	ft_add_nl_last_row(t, t->inp, 0);
	t->c_col = write(1, PROMPT, (size_t)t->prompt_len);
	while (t->ch != -1)
	{
		t->ch = ft_get_input();
		if (ft_isprint_or_enter(t))
			return (0);
		if (t->ch == CTRL_D)
		{
			ctrl_d_ret = ctrl_d(t);
			if (ctrl_d_ret == 1)
				continue ;
			if (ctrl_d_ret == -1)
				return (ctrl_d_exit());
		}
		ft_ctrl(t);
		ft_backspace_or_escape(t);
		ft_bslash_handling(t);
		if (t->ch == -1)
			ft_putstr_fd("error, ft_get_input()\n", STDERR_FILENO);
	}
	return (0);
}
