/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 05:56:33 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/18 16:27:29 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/incs/libft.h"

/* Mandatory */
# include	<sys/stat.h>

# ifdef __linux__
#  include	<sys/wait.h>
# endif

/* Bonus */
# include <sys/ioctl.h>
# include <dirent.h>

# define RESET 0
# define ERROR 1
# define INVALID -1
# define NOACCESS -2
# define TOOMANYARGS -3
# define NOCOMMAND -4
# define ERR_NOMEM -5
# define NONEXE -6
# define START 0
# define END 1

# define PROMPT "{RED}SuperPinoyBoy:> {RESET}"
# define MAXPATHLEN 1024

typedef struct dollar_attr
{
	int		i;
	bool	match;
	char	**keys;
}				t_dollar;

typedef struct tokens
{
	bool	*tok;
	char	**arg;
}				t_tokens;

typedef struct sesssion
{
	char		**env;
	t_tokens	*tok;
	char		**tm_en;
	int			result;
}				t_session;

/* Initialising Environment Variables */
char	**env_init(void);
char	**mandatory_env(t_session *sesh);
char	*shlvl(char *my_env, char *env);

/* PARSER */
char	*get_extra(char **keys);
void	user_expansion(char **arg);
void	tilda_parse(t_session *sesh);
void	dollar_parse(t_session *sesh);
char	*prefix(char **arg, char *str);
void	arg_qty_loop(char *line_cpy, int *len);
int		get_args(t_session *sesh, char **line);
void	find_match_env(char **arg, char **env, t_dollar *attr);
void	collect_args_loop(char **args, char *line, bool *tok, int *i);

/* EXIT */
void	no_mem_exit(void);
void	env_clean(char **env);
void	arg_clean(t_tokens *toks);
void	ft_exit(t_session *session, char *message, int status);

/* Printing header */
void	header_print(void);

/* Cycle */
void	cycle(t_session *sesh, bool pos);

/* System Call */
int		system_call(t_session *sesh);

/* Error messages */
void	error_message(t_session *sesh);

/* Builtins */
int		built_ins(t_session *session);
int		cmd_echo(char **arg);
int		cmd_env(t_session *sesh);
int		cmd_setenv(t_session *session);
int		cmd_unsetenv(t_session *session);
int		cmd_cd(t_session *sesh);

/* Builtins Utils */
void	cd_success(t_session *sesh);

/* Utils */
int		check_address(char *file);
char	*skip_whitespace(char *str);
int		array_len(char **env, bool pos);
int		append_env(t_session *sesh, char **arg);
int		env_removal(t_session *sesh, char *env);
char	**env_get_var(t_session *sesh, char *key);
char	**env_last_prog(char *path, t_session *sesh);
bool	replace_value(t_session *sesh, char *arg, char **tmp);

#endif
