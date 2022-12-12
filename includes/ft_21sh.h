/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 09:30:27 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/12 11:34:37 by mbarutel         ###   ########.fr       */
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
	t_pipenode pipe;
	t_cmdnode cmd;
	t_redir redir;
	t_aggregate aggregate;
};

/*				SESSION STRUCT				*/
typedef struct session
{
	t_treenode		*head;
	char			**env;
	t_token			*tokens;
	int				exit_stat;
	char			*terminal;
	char			**tmp_env_key;
	struct termios	orig_termios;
}				t_session;

/*					HEADER					*/
void	banner_print(void);

/*				   MAIN LOOP				*/
void	reset_filedescriptors(t_session *sesh);
void			shell_end_cycle(t_session *sesh);
void			reset_fd(char *terminal);
char			*str_from_arr(char **arr);
struct termios	ft_raw_enable(void);
int				ft_getent(void);
void			ft_raw_disable(struct termios orig_termios);


/*				  INITIALIZE				*/
void	ft_env_init(t_session *sesh);
void	ft_session_init(t_session *sesh);

/*					LEXER					*/
char	*ft_lexer(t_term *t);

/*					TOKENIZER				*/
t_token *chop_line(char *line, t_token *args, size_t pointer_n);
void 	free_token(t_token *token);
void	free_tokens(t_token *tokens);
int 	is_ws(char c);

/*					BULDTREE				*/
t_treenode *build_tree(t_token *tokens);
char **make_arg_array(char *cmd);

/*					EXPANSION				*/
void	ft_expansion(t_session *sesh, char **cmd);
char	*ft_expansion_dollar(t_session *sesh, char *str);
char	*ft_expansion_tilde(t_session *sesh, char *str);

/*					UTILITIES				*/
int		ft_addr_check(char *file);
char	**ft_env_get(t_session *sesh, char *key);
int		increment_whitespace(char **line);
void	free_node(t_treenode *head);

/*					EXECUTE_TREE			*/
void	exec_tree(t_treenode *head, char ***environ_cp, char *terminal, t_session *sesh);
void	execute_bin(char **args, char ***environ_cp, t_session *sesh);
void	exec_pipe(t_pipenode *pipenode, char ***environ_cp, char *terminal, t_session *sesh);
void	exec_redir(t_redir *node, char ***environ_cp, char *terminal, t_session *sesh);
void	exec_aggregate(t_aggregate *node, char ***environ_cp, char *terminal, t_session *sesh);
void	exec_closefd(t_closefd *node, char ***environ_cp, char *terminal, t_session *sesh);
char	*search_bin(char *cmd, char **environ_cp);
void	error_exit(char *msg);
int		ft_freeda(void ***a, size_t row);
size_t	calc_chptr(char **arr);
int		fork_wrap(void);

/*			   		 BUILTIN	  			*/
int		ft_builtins(t_session *sesh, char **cmd);
int		ft_cd(t_session *sesh, char **cmd);
int		ft_echo(char **cmd);
int		ft_env(t_session *sesh, char ***cmd);
void	ft_exit(t_session *sesh, int status);
int		ft_setenv(t_session *sesh, char **cmd);
int		ft_unsetenv(t_session *sesh, char **cmd);

/*			    BUILTIN UTILITIES			*/
int		ft_env_temp(t_session *sesh, char **cmd, int i);
void	ft_env_remove(t_session *sesh, char *env_to_clean);
int		ft_env_append(t_session *sesh, char **arg);
int		ft_env_replace(t_session *sesh, char *envn, char **tmp_env);
void	ft_dir_change(t_session *sesh);

#endif


