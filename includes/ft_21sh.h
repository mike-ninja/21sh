/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 09:30:27 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/22 19:50:49 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_21SH_H
# define FT_21SH_H

# include "libft.h"
# include "keyboard.h"
# include "ft_printf.h"

typedef struct	s_branch
{
	int		type;
	char	*arg[100];
	struct	s_branch *left;
	struct	s_branch *right;
	struct	s_branch *command;
}				t_branch;

//# define TOKEN_POINTER_N 1
/* Do not use zero */
# define PIPE		1
# define CMD		2
# define REDIR		3
# define WORD		4
# define SEMICOLON	5
# define NEWLINE	6

/*					TOKEN STRUCT			*/
typedef struct s_token
{
	int		token;
	char	*value;
}	t_token;

/*					CMD STRUCT				*/
typedef struct s_cmdnode
{
	int		type;
	char	**cmd;
} t_cmdnode;

typedef union u_treenode t_treenode;
/*					REDIR STRUCT			*/
typedef struct s_redir
{
	int			type;
	t_treenode	*cmd;
	int			close_fd;
	char		*filepath;
	int			open_flags;
	int			rights;
} t_redir;

/*					PIPE STRUCT				*/
typedef struct s_pipenode
{
	int			type;
	t_treenode	*left;
	t_treenode	*right;
}	t_pipenode;

/*					TREE UNION				*/
union u_treenode
{
	int	type;
	t_pipenode	pipe;
	t_cmdnode	cmd;
	t_redir		redir;
};

/*					HEADER					*/
void	banner_print(void);

/*					LEXER					*/
char	*ft_lexer(char *str);

/*					TOKENIZER				*/
t_token	*chop_line(char *line, t_token *args, size_t pointer_n);

/*					BULDTREE				*/
void	build_tree(t_token *tokens);

#endif
