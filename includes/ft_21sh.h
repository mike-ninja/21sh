/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 09:30:27 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/21 13:36:39 by jniemine         ###   ########.fr       */
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

# define TOKEN_POINTER_N 1

typedef struct s_token
{
	char	*token;
	char	*value;
}	t_token;

/*					HEADER					*/
void	banner_print(void);

/*					LEXER					*/
char	*ft_lexer(char *str);

/*					TOKENIZER				*/
t_token	*chop_line(char *line, t_token *args, size_t pointer_n);

#endif
