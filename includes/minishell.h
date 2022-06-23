
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
#include 	<fcntl.h>
# include	"../libft/libft.h"

typedef struct tokens {
	int				size;
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
	int		herdoc;
	char 	**delims;
	char	*del;
	int		flag;
	struct	command *next;
} t_cmd;


//checker functions
void				ft_check(char *command);
int     			command_checker(char *command);

//lists_utils_functions
void   				add_front(t_token** head, char *data);
void				add_to_end(t_token** head, t_token *data);
void    			list_clear(t_token** head_ref);
void				delete_node(t_token** head, t_token *del_node);
int					lstsize(t_token *lst);
//cmds list_utls
void    			add_cmd_to_end(t_cmd** command, char **new_data);
t_cmd				*new_cmd_token(char **data);
void				clear_cmds(t_cmd** head_ref);
void				delete_cmd(t_cmd** head, t_cmd *del_node);

t_token				*new_token(char *data, int size, t_token_type type);
static t_token_type	token_found(const char *cmd_line);
int					get_word_token_size(char *cmd_line);
void				get_next_token(char *cmd_line, int *size, t_token_type *type);

//tokenizer_utils
t_token				*ft_tokens(char *line);
char				*ft_strncpy(char *dst, const char *src, int len);
char				*ft_sub_str(const char *src, int len);
void				remove_all_chars(char* str, char c);
int					is_quotes(char *tok);

//Flaging Functions 
void				flag_list(t_token *list);
void				add_flag(t_token *tmp);
int					check_cmd(char *tok);
int					wich_redirection(char *red);

//Syntax analyser
int					invalid_token(char *node);
int					is_operator(char *tok);
int					syntax_validation(t_token *list);

//parser
t_cmd				*creat_cmds(t_token *node);
char				**remplir_tab(t_token *node, int start);
int					count_size(t_token	*node, int start);
void				remove_quotes(t_cmd *node);

//epand dollar
void				expand_dollar(t_cmd *node);

//expander_utils
char				*dollar_substr1(char *str);
char				*dollar_substr(char *str);
int					is_dollar(char *str);
int					get_env_end(char *str);
const char			*ft_strstr(const char *str, const char *to_find);

//files creation
void				ft_free(char *s1, char *s2);
int					is_redirection(char *tok);
int					is_file(t_cmd *node);
int					open_redirect_input(char *file, t_cmd *node);
void				open_app_redirect_out(char *file, t_cmd *node);
void				open_redirect_out(char *fl, t_cmd *node);
void				ft_input_file(t_cmd *node, int *i);
int					ft_open(t_cmd *node);
void				open_files(t_cmd *node);

// herduq

char				*ft_strjoin_1(char *s1, char *s2);
void				create_delimters(t_cmd *node, int *i);

#endif