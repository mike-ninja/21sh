/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:51:26 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/18 17:38:36 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYBOARD_H
# define KEYBOARD_H

# include <termcap.h>//control if all these are needed
# include <ft_vec.h>
# include <term.h>//same same
# include <fcntl.h>
# include <curses.h>//same same
# include <signal.h>
# include <termios.h>
# include <sys/ioctl.h>

# define DEL		0x0000
# define BCK		0x0001

# define CTRL_C		0x0003
# define CTRL_D		0x0004

# define D_QUO		0x0022
# define S_QUO		0x0027

# define ESCAPE     0x001B
# define ENTER      0x000A
# define DOWN		0x0105
# define UP			0x0106
# define LEFT       0x0107
# define RIGHT      0x0108
# define BACKSPACE	0x007F
# define TAB		0x0009

# define PROMPT		"$> "
# define M_PROMPT	"> "

# define BUFFSIZE   2048
# define MAX_LINE   1024

typedef struct s_term
{
	int		ch;
	char	quote;
	ssize_t	q_qty;
	ssize_t	index;
	ssize_t	bytes;
	ssize_t	c_row;
	ssize_t	c_col;
	ssize_t	ws_col;
	ssize_t	ws_row;
	ssize_t	start_row;
	ssize_t	total_row;
	ssize_t	prompt_len;
	ssize_t	m_prompt_len;
	ssize_t	total_row_cpy;
	t_vec	v_history;
	char	**nl_addr;
	char	*input_cpy;
	char	*history_file;
	char	inp[BUFFSIZE];
}			t_term;

int		ft_keyboard(t_term *t);
void	ft_init(t_term *t);
void	ft_input_cycle(t_term *t);
int		ft_putc(int c);
void	ft_restart_cycle(t_term *t);
void	ft_clearscreen(void);
void	ft_setcursor(ssize_t col, ssize_t row);
void	ft_run_capability(char *cap);
void	ft_window_size(t_term *t);
void	ft_init_signals(void);
int		ft_get_linenbr(void);
ssize_t	ft_len_lowest_line(t_term *t, ssize_t row);

/*				History				*/
void	ft_history(t_term *t);
char	*ft_history_file_get(void);
void	ft_history_get(t_term *t);
void	ft_history_write_to_file(t_term *t);
void	ft_history_trigger(t_term *t, ssize_t his);

/*		    Cursor Movement			*/
void	ft_opt_mv(t_term *t);
void	ft_line_mv(t_term *t);
void	ft_word_mv(t_term *t);

/*		  Printing to Display		*/
ssize_t	ft_display_row(t_term *t, ssize_t c_row);
void	ft_print_trail(t_term *t);

/*		   New Line Mangement		*/
void	ft_shift_nl_addr(t_term *t, int num);
ssize_t	get_last_non_prompt_line(t_term *t);
ssize_t	ft_get_prompt_len(t_term *t, ssize_t row);
void	nl_addr_reset(t_term *t);
void	ft_remove_nl_addr(t_term *t, ssize_t row);
void	ft_reset_nl_addr(t_term *t);
char	*ft_is_prompt_line(t_term *t, ssize_t row);
void	nl_terminal_size(t_term *t);
void	ft_add_nl_last_row(t_term *t, ssize_t pos);
void	ft_add_nl_mid_row(t_term *t, ssize_t row, ssize_t pos);

/*		     Quote Handling 		*/
void	ft_quote_handling(t_term *t, char ch);
void	ft_quote_decrement(t_term *t, int num);

/*		        Deletion	 		*/
ssize_t	ft_row_lowest_line(t_term *t);
void	ft_delete(t_term *t);
void	ft_backspace(t_term *t);
void	ft_deletion_shift(t_term *t, int mode);

/*		       Insertion	 		*/
int		ft_get_input(void);
void	ft_insertion(t_term *t);
void	ft_arrow_input(t_term *t);
void	ft_esc_parse(t_term *t);
void	ft_create_prompt_line(t_term *t, ssize_t loc);

#endif
