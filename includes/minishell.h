/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houazzan <houazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:07:29 by houazzan          #+#    #+#             */
/*   Updated: 2022/05/27 18:45:43 by houazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H
enum coammands_list {COMMAND = 1, WORD, D_QUOTES, S_QUOTES, 
					O_REDIRECTION, I_REDIRECTION, 
					ASO, ASI, OPTION, FL, DOLLAR};//ASO/ASI : appending standard output/input (>>/<<)

# include	<stdio.h>
# include	<stdlib.h>
# include	<string.h>
# include	<readline/readline.h>
# include	<readline/history.h>
# include	<errno.h>
# include	"../libft/libft.h"

typedef struct tokens {
	char    *data;
	int		key;
	struct	tokens *next;
	struct	tokens *prev;
} t_token;

typedef struct command {
	char    **cmd;
	struct	command *next;
	struct	command *prev;
} t_cmd;

//checker functions
void	ft_check(char *command);
int     command_checker(char *command);

//lists_utils_functions
void    add_front(t_token** head, char *data);
void	add_to_end(t_token** head, char *data, int ident);
void    list_clear(t_token** head_ref);
void	delete_node(t_token** head, t_token *del_node);
int		lstsize(t_token *lst);

//tokenizer_utils
t_token	*ft_tokens(char *line);
//utils1
int		ft_isspace(char c);
char	*ft_strndup(char *str, int n);
char	*ft_normal(char *line, int start);

//utils2_quotes_tokens
char	*ft_double_quote(char *line, int start);
char	*ft_single_quote(char *line, int start);
void	tokenize_quotes(t_token **list, char *line, int *i);
void	double_quotes(t_token **list, char *line, int *i);
void	single_quotes(t_token **list, char *line, int *i);

//utils3_redirections_tokens
int		check_redirection(char *tok);
char	*ft_redirection(char *tok, int n);
void	redirections(t_token **list, char *line, int *i);
void	redirection1(t_token **list, char *tok, char *line, int *i);

//utils3_dollar_tokens
int		have_space(char *tok);
int		is_dollar(char *tok);
void	ft_dollar(t_token **list, char *tok);

//Syntax analyser
int		invalid_token(char *node);
int		is_operator(char *tok);
int		syntax_validation(t_token *list);

#endif