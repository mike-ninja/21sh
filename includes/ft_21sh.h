/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 09:30:27 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/27 20:32:16 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_21SH_H
#define FT_21SH_H

#include "libft.h"
#include "keyboard.h"
#include "ft_printf.h"
/* DUNNO IF NEEDED */
#include <sys/stat.h>
#include <sys/wait.h>
/* DUNNO IF NEEDED */

typedef struct s_branch
{
	int type;
	char *arg[100];
	struct s_branch *left;
	struct s_branch *right;
	struct s_branch *command;
} t_branch;

//# define TOKEN_POINTER_N 1
/* Do not use zero */
#define PIPE 1
#define CMD 2
#define REDIR 3
#define WORD 4
#define SEMICOLON 5
#define NEWLINE 6

/* Build tree, redir types */
#define RE_IN_ONE 1
#define RE_IN_TWO 2
#define RE_IN_TRI 3
#define RE_OUT_ONE 4
#define RE_OUT_TWO 5

/*					TOKEN STRUCT			*/
typedef struct s_token
{
	int token;
	char *value;
} t_token;

/*					CMD STRUCT				*/
typedef struct s_cmdnode
{
	int type;
	char **cmd;
} t_cmdnode;

typedef union u_treenode t_treenode;
/*					REDIR STRUCT			*/
typedef struct s_redir
{
	int type;
	t_treenode *cmd;
	int close_fd;
	char *filepath;
	int open_flags;
	int rights;
} t_redir;

/*					PIPE STRUCT				*/
typedef struct s_pipenode
{
	int type;
	t_treenode *left;
	t_treenode *right;
} t_pipenode;

/*					TREE UNION				*/
union u_treenode
{
	int type;
	t_pipenode pipe;
	t_cmdnode cmd;
	t_redir redir;
};

/*					HEADER					*/
void	banner_print(void);

/*				   MAIN LOOP				*/
void	ft_endcycle(t_session *sesh);

/*				  INITIALIZE				*/
void	ft_session_init(t_session *sesh);
char	**ft_env_init(void);

/*				   MAIN LOOP				*/
void	ft_endcycle(t_session *sesh);

/*				  INITIALIZE				*/
void	ft_session_init(t_session *sesh);
char	**ft_env_init(void);

/*					LEXER					*/
void	ft_lexer(char *str, char **line);

/*					TOKENIZER				*/
t_token *chop_line(char *line, t_token *args, size_t pointer_n);
void free_token(t_token *token);
int is_ws(char c);

/*					BULDTREE				*/
void build_tree(t_token *tokens);

/*					EXPANSION				*/
void	ft_expansion(t_session *sesh);
char	*ft_expansion_dollar(t_session *sesh, char *str);
char	*ft_expansion_tilde(t_session *sesh, char *str);

/*					UTILITIES				*/
int		ft_addr_check(char *file);
char	**ft_env_get(t_session *sesh, char *key);

/*					EXECUTE_TREE			*/
void exec_tree(t_treenode *head, char ***environ_cp);
void	execute_bin(char **args, char ***environ_cp);
char	*search_bin(char *cmd, char **environ_cp);
void exec_pipe(t_pipenode *pipenode, char ***environ_cp);
void exec_redir(t_redir *node, char ***environ_cp);
void	error_exit(char *msg);
int	ft_freeda(void ***a, size_t row);
size_t	calc_chptr(char **arr);
#endif
