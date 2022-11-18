# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/12 06:01:22 by mbarutel          #+#    #+#              #
#    Updated: 2022/10/18 21:09:59 by mbarutel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	 = minishell

CC 		= gcc
INC 	= -Iincs/
FLAG 	= -Werror -Wextra -Wall

LIBFT 		= libft
LIBFT_INC	= -Llibft -lft
SRC_DIR 	= srcs/
OBJ_DIR 	= objs/
TERMCAP		= -ltermcap
# FSANITIZE	= -g -fsanitize=address

# Colors
DEF_COLOR 	= \033[0;39m
RED 		= \033[1;91m
BLUE 		= \033[1;94m
MAGENTA 	= \033[1;95m
CYAN 		= \033[1;96m

FILE = main
FILE += init_env
FILE += init_env_utils
FILE += args_parse
FILE += args_parse_utils
FILE += tilda_parse
FILE += dollar_parse
FILE += parse_utils
FILE += built_ins
FILE += exit
FILE += cmd_cd
FILE += cmd_cd_utils
FILE += cmd_env
FILE += cmd_setenv
FILE += cmd_unsetenv
FILE += header
FILE += cycle
FILE += system_call
FILE += user_expansion
FILE += errors
FILE += utils

OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILE)))

all: $(NAME)

$(NAME): $(OBJ) Makefile
	@make -C $(LIBFT)
	@$(CC) $(FLAG) $(FSANITIZE) $(OBJ) -o $@ $(TERMCAP) $(LIBFT_INC)
	@echo "$(BLUE)Generated Executable -> $@$(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@$(CC) -c $(INC) $(FLAG) $< -o $@
	@echo "$(CYAN)Generated Object File -> $<$(DEF_COLOR)"

$(OBJ_DIR):
	@mkdir -p $@

clean:
	@make clean -C $(LIBFT)
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)Deleted Objects Directory -> $(NAME)$(DEF_COLOR)"

fclean: clean
	@make fclean -C $(LIBFT)
	@rm -f $(NAME)
	@echo "$(MAGENTA)Deleted Library -> $(NAME)$(DEF_COLOR)"
	
re: fclean $(OBJ_DIR) all

.PHONY: all clean fclean re
