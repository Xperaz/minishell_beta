# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/25 13:56:52 by aouhadou          #+#    #+#              #
#    Updated: 2022/06/26 16:37:35 by aouhadou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc 

FLAGS = -Wall -Wextra -Werror

SRCF = sources/

SRC  = minishell.c checker.c list_utils.c lis_utils2.c \
	tokenizer.c toknizer_utils.c \
	syntax_validation.c \
	cmd_list_utils.c parser.c parser_utils.c \
	expander.c expander_utils.c files_creation.c \
	files_creation_utils.c heredoc_utils.c signals.c \

SRCP = $(addprefix $(SRCF), $(SRC))

OBJ = $(SRCP:%.c=%.o)

NAME = minishell

all  :$(NAME)

$(NAME) : $(OBJ) 
		@$(CC) $(FLAGS) ./libft/libft.a $(OBJ) -o $(NAME) -lreadline -L$(shell brew --prefix readline)/lib
		@echo "$(GREEN) " MINISHELL DONE" $(RESET)\n"

%.o : %.c includes/minishell.h
	@make -C ./libft
	@$(CC) $(FLAGS) -I$(shell brew --prefix readline)/include -c $< -o $@ 
	@echo "$(CHANGE)$(GREEN)∰$(RESET)\c"

clean :
		@rm -rf $(OBJ)
		@make fclean -C ./libft

fclean : clean
		@rm -rf $(NAME)
re		: clean all


.PHONY : all clean fclean re


GREEN = \033[0;32m
RED = \033[0;31m
PURPLE = \033[0;35m
CYAN = \033[0;36m
RESET = \033[0m
YELLOW = \033[0;33m
BLUE = \033[0;34m
CHANGE = \033[0;35m
TAB = "\	"
