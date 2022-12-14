/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 09:30:27 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/14 18:58:26 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_21SH_H
#define FT_21SH_H

#include "libft.h"
#include "keyboard.h"
#include "ft_printf.h"
/* DUNNO IF NEEDED */
#include <dirent.h>
#include <sys/stat.h>
#include <sys/wait.h>

//# define TOKEN_POINTER_N 1
/* Do not use zero */
#define PIPE 1
#define CMD 2
#define REDIR 3
#define WORD 4
#define SEMICOLON 5
#define AGGREGATION 7
#define CLOSEFD 8

/* For error messages */
#define SHELL_NAME "21sh"

/* Build tree, redir types */
#define RE_IN_ONE 1
#define RE_IN_TWO 2
#define RE_IN_TRI 3
#define RE_OUT_ONE 4
#define RE_OUT_TWO 5

typedef union u_treenode t_treenode;

/*					TOKEN STRUCT			*/
typedef struct s_token
{
	int token;
	char *value;
} t_token;

/*					SEMICOLON STRUCT		*/
typedef struct s_semicolon
{
	int type;
	t_treenode *left;
	t_treenode *right;
}	t_semicolon;

/*					CMD STRUCT				*/
typedef struct s_cmdnode
{
	int type;
	char **cmd;
}	t_cmdnode;

/*					CLOSEFD STRUCT			*/
typedef struct s_closefd
{
	int			type;
	int			close_fd;
	t_treenode	*cmd;
}	t_closefd;

/*					REDIR STRUCT			*/
typedef struct s_redir
{
	int			type;
	t_treenode	*cmd;
	int			close_fd;
	char		*filepath;
	int			open_flags;
	int			rights;
}				t_redir;

/*					AGGREGATION	STRUCT		*/
typedef struct s_aggregation
{
	int			type;
	t_treenode	*cmd;
	int			close_fd;
	int			open_fd;
} t_aggregate;


/*					PIPE STRUCT				*/
typedef struct s_pipenode
{
	int			type;
	t_treenode	*left;
	t_treenode	*right;
}				t_pipenode;

/*					TREE UNION				*/
union u_treenode
{
	int type;
	t_semicolon semicolon;
	t_pipenode pipe;
	t_cmdnode cmd;
	t_redir redir;
	t_aggregate aggregate;
	t_closefd	closefd;
};

/*				SESSION STRUCT				*/
typedef struct session
{
	char			*line;
	t_treenode		*head;
	char			**env;
	t_token			*tokens;
	int				exit_stat;
	char			*terminal;
	char			**tmp_env_key;
	struct termios	orig_termios;
}				t_session;

/*					HEADER					*/
void			banner_print(void);

/*				   MAIN LOOP				*/
void			shell_end_cycle(t_session *sesh);
void			reset_fd(char *terminal);
char			*str_from_arr(char **arr);
struct termios	ft_raw_enable(void);
int				ft_getent(void);
void			ft_raw_disable(struct termios orig_termios);


/*				  INITIALIZE				*/
void			ft_env_init(t_session *sesh);
void			ft_session_init(t_session *sesh);

/*					LEXER					*/
char			*ft_lexer(t_term *t);

/*					TOKENIZER				*/
t_token 		*chop_line(char *line, t_token *args, size_t pointer_n);
void 			free_token(t_token *token);
void			free_tokens(t_token *tokens);
char			*find_argument(char *line, int *i, int *start, int *end);
int 			is_ws(char c);
void			init_token(char *c, t_token *token, char *line, int cur);
void			track_used_space(t_token **args, size_t current_pointer_n
				, size_t *max_pointer_n);


/*					TOKENIZER UTILS			*/
void			free_tokens(t_token *tokens);
void			free_token(t_token *token);
int				is_nl(char c);
int				is_ws(char c);
int				is_seperator(char c);

/*					BUILDTREE				*/
t_treenode		*build_tree(t_token *tokens);
char			**make_arg_array(char *cmd);
void			print_tree(t_treenode *head, int depth);
int				foreseer_of_tokens(t_token *tokens, int mark, int start, int end);
t_treenode		*create_pipe_node(t_token *tokens, int i_tok);
t_treenode		*create_semicolon_node(t_token *tokens, int i_tok, int end);
t_treenode		*parse_left_cmd(t_token *tokens, int i_tok);
t_treenode		*parse_right_cmd(t_token *tokens, int i_tok);
t_treenode		*parse_redirections(t_token *tokens, int i_tok, int cmd);
t_treenode		*init_cmd_node(char *cmd);
int				calculate_tokens(t_token *tokens);
int				choose_redir_type(t_token *tokens, t_treenode **redir, int i_tok, int cmd);
int				if_closefd(t_token *tokens, t_treenode **redir, int i_tok, int cmd);
int				if_aggregation(t_token *tokens, t_treenode **redir, int i_tok, int cmd);
int				if_redir(t_token *tokens, t_treenode **redir, int i_tok, int cmd);
int				get_close_fd(char *value);
void			traverse_node(t_treenode **head);
char			*get_file(char *value);
int				error_tok(t_token *tokens, t_treenode *redir_head, char *msg, char *symbol); //Check this

/*					EXPANSION				*/
void			ft_expansion(t_session *sesh, char **cmd);
char			*ft_expansion_dollar(t_session *sesh, char *str);
char			*ft_expansion_tilde(t_session *sesh, char *str);

/*					UTILITIES				*/
int				ft_addr_check(char *file);
char			**ft_env_get(t_session *sesh, char *key);
int				increment_whitespace(char **line);
void			free_node(t_treenode *head);

/*					EXECUTE_TREE			*/
void			exec_tree(t_treenode *head, char ***environ_cp, char *terminal, t_session *sesh);
void			execute_bin(char **args, char ***environ_cp, t_session *sesh);
void			exec_pipe(t_pipenode *pipenode, char ***environ_cp, char *terminal, t_session *sesh);
void			exec_redir(t_redir *node, char ***environ_cp, char *terminal, t_session *sesh);
void			exec_aggregate(t_aggregate *node, char ***environ_cp, char *terminal, t_session *sesh);
void			exec_closefd(t_closefd *node, char ***environ_cp, char *terminal, t_session *sesh);
char			*search_bin(char *cmd, char **environ_cp);
void			error_exit(char *msg);
int				ft_freeda(void ***a, size_t row);
size_t			calc_chptr(char **arr);
int				fork_wrap(void);
void			open_fd_if_needed(int fd, char *terminal);

/*					ERROR					*/
void 			exe_cmd_err(char *msg, char *cmd);

/*					BUILTIN					*/
int		ft_builtins(t_session *sesh, char ***cmd);
int		ft_cd(t_session *sesh, char **cmd);
int		ft_echo(char **cmd);
int		ft_env(t_session *sesh, char ***cmd);
void	ft_exit(t_session *sesh, int status);
int		ft_setenv(t_session *sesh, char **cmd);
int		ft_unsetenv(t_session *sesh, char **cmd);

/*			    BUILTIN UTILITIES			*/
int				ft_env_temp(t_session *sesh, char **cmd, int i);
void			ft_env_remove(t_session *sesh, char *env_to_clean);
int				ft_env_append(t_session *sesh, char **arg);
int				ft_env_replace(t_session *sesh, char *envn, char **tmp_env);
void			ft_dir_change(t_session *sesh);

#endif
