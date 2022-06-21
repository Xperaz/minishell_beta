CC = gcc 

FLAGS = -Wall -Wextra -Werror -lreadline 

SRCF = sources/

SRC  = minishell.c checker.c list_utils.c \
	tokenizer.c toknizer_utils.c \
	syntax_validation.c add_flag.c\
	cmd_list_utils.c parser.c parser_utils.c

SRCP = $(addprefix $(SRCF), $(SRC))

OBJ = $(SRCP:%.c=%.o)

NAME = minishell

all  :$(NAME)

$(NAME) : $(OBJ) 
		@$(CC) $(FLAGS) ./libft/libft.a $(OBJ) -o $(NAME) -lreadline -L$(shell brew --prefix readline)/lib
		@echo "$(GREEN) " MINISHELL DONE" $(RESET)\n"

%.o : %.c includes/minishell.h
	@make -C ./libft
	@$(CC) $(CFLAGS) -I$(shell brew --prefix readline)/include -c $< -o $@ 
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
