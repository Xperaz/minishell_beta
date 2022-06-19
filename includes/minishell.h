
#ifndef MINISHELL_H

# define MINISHELL_H

typedef enum e_token_type		t_token_type;

enum coammands_list {COMMAND = 1, WORD, O_REDIRECTION, I_REDIRECTION, 
					ASO, HERDOC, DELIMTER, OPTION, FL, DOLLAR, PIPE, DOUBLE};//ASO/ASI : appending standard output/input (>>/<<)
enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	INPUT,
	AS_input,
	OUTPUT,
	AS_output,
	TOKEN_START,
	TOKEN_LINE,
	D_QUOTES = 10,
};

# include	<stdio.h>
# include	<stdlib.h>
# include	<string.h>
# include	<readline/readline.h>
# include	<readline/history.h>
# include	<errno.h>
# include	"../libft/libft.h"

typedef struct tokens {
	int				size;
	int				dq;
	t_token_type	type;
	char			*data;
	int				key;
	int				taille;
	struct	tokens *next;
	struct	tokens *prev;
} t_token;

typedef struct command {
	char    **cmd;
	int		infile;
	int		outfile;
	struct	command *next;
} t_cmd;

//checker functions
void	ft_check(char *command);
int     command_checker(char *command);

//lists_utils_functions
void    add_front(t_token** head, char *data);
void	add_to_end(t_token** head, t_token *data);
void    list_clear(t_token** head_ref);
void	delete_node(t_token** head, t_token *del_node);
int		lstsize(t_token *lst);

t_token	*new_token(char *data, int size, t_token_type type);
static t_token_type	token_found(const char *cmd_line);
int	get_word_token_size(char *cmd_line);
void	get_next_token(char *cmd_line, int *size, t_token_type *type);

//tokenizer_utils
t_token	*ft_tokens(char *line);
char	*ft_strncpy(char *dst, const char *src, int len);
char	*ft_sub_str(const char *src, int len);
void	remove_all_chars(char* str, char c);
int		is_quotes(char *tok);

//Flaging Functions 
void	flag_list(t_token *list);
void	add_flag(t_token *tmp);
int		check_cmd(char *tok);
int		wich_redirection(char *red);

//Syntax analyser
int		invalid_token(char *node);
int		is_operator(char *tok);
int		syntax_validation(t_token *list);

#endif