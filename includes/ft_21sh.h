/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 09:30:27 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/23 14:46:56 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_21SH_H
# define FT_21SH_H

# include "libft.h"
# include "keyboard.h"
# include "ft_printf.h"

# define TOKEN_POINTER_N 1

typedef struct	s_branch
{
	int		type;
	char	*arg[100];
	struct	s_branch *left;
	struct	s_branch *right;
	struct	s_branch *command;
}				t_branch;

typedef struct	s_token
{
	char	*token;
	char	*value;
}				t_token;

typedef struct sesssion
{
	int			ret;
	char		**env;
	t_token		*tokens;
	char		**tmp_env;
}				t_session;

/*					HEADER					*/
void	banner_print(void);

/*				  INITIALIZE				*/
void	ft_session_init(t_session *sesh);
char	**ft_env_init(void);

/*					LEXER					*/
char	*ft_lexer(char *str);

/*					TOKENIZER				*/
t_token	*chop_line(char *line, t_token *args, size_t pointer_n);

/*					EXPANSION				*/
void	ft_expansion(t_session *sesh);
char	*ft_expansion_dollar(t_session *sesh, char *str);
char	*ft_expansion_tilde(t_session *sesh, char *str);

/*					UTILITIES				*/
int		ft_addr_check(char *file);
char	**ft_env_get(t_session *sesh, char *key);

#endif
