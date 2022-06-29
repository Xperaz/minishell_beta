/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 15:46:02 by aouhadou          #+#    #+#             */
/*   Updated: 2022/06/28 19:16:16 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSE_H
# define PARSE_H

# define errors	"shell$> : syntax error unexpected token"

//checker functions
void				ft_check(char *command);
int     			command_checker(char *command);
void				print_error();
int					ft_strcmp1(char *s1, char *s2);

//lists_utils_functions
void   				add_front(t_token** head, char *data);
void				add_to_end(t_token** head, t_token *data);
void    			list_clear(t_token** head_ref);
void				delete_node(t_token** head, t_token *del_node);
int					lstsize(t_token *lst);
//cmds list_utls
void    			add_cmd_to_end(t_command** command, char **new_data);
t_command				*new_cmd_token(char **data);
void				clear_cmds(t_command** head_ref);
void				delete_cmd(t_command** head, t_command *del_node);
int					lstsize2(t_command *lst);

t_token				*new_token(char *data, int size, t_token_type type);
t_token_type		token_found(const char *cmd_line);
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
t_command				*creat_cmds(t_token *node);
char				**remplir_tab(t_token *node, int start);
int					count_size(t_token	*node, int start);
int					remove_quotes(t_command *node);

//epand dollar
void				expand_dollar(t_command *node);

//expander_utils
char				*dollar_substr1(char *str);
char				*dollar_substr(char *str);
int					is_dollar(char *str);
int					get_env_end(char *str);
const char			*ft_strstr(const char *str, const char *to_find);

//files creation
void				ft_free(char *s1, char *s2);
int					is_redirection(char *tok);
int					is_file(t_command *node);
int					open_redirect_input(char *file, t_command *node);
void				open_app_redirect_out(char *file, t_command *node);
void				open_redirect_out(char *fl, t_command *node);
void				ft_out_file(t_command *node, int *i);
int					ft_open(t_command *node);
void				open_files(t_command *node);

// herduq
char				*ft_strjoin_1(char *s1, char *s2);
void				create_delimters(t_command *node, int *i);

//Remove unused arrays

void    ft_remove_unsed(t_command *node);

//signals
void				handle_sig(int sig);
void				ctrl_d();

#endif