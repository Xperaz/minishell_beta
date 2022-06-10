/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houazzan <houazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:08:16 by houazzan          #+#    #+#             */
/*   Updated: 2022/05/28 13:20:04 by houazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void display(t_token* node) {

	t_token	*tmp;
	tmp = node;
  while (tmp != NULL) {
    printf("{%s} ", tmp->data);
    tmp = tmp->next;
  }
  printf("\n");
}


/* **************************************************** */
/*                     SYNTAX_ANALYZER.                 */
/* **************************************************** */

int	invalid_token(char *node)
{
	int	i;

	i = 0;
	if (!ft_strncmp(node, "()", 2) || !ft_strncmp(node, "||", 2) || !ft_strncmp(node, "&&", 2))
		return (0);
	return (1);
}

int	is_redirection(char *tok)
{
	if (!ft_strncmp(tok, ">", 1) || !ft_strncmp(tok, "<", 1)
			|| !ft_strncmp(tok, ">>", 2) || !ft_strncmp(tok, "<<", 1))
			return (1);
	return (0);	
}

int		syntax_validation(t_token	*list)
{
	t_token	*tmp;

	tmp = list;
	int flag = 0;
	while (tmp != NULL)
	{
		if (!invalid_token(tmp->data))
			return (0);
		else if (is_redirection(tmp->data) &&
			(tmp->next == NULL || is_redirection(tmp->next->data)))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	ft_lexer(char *line)
{
	t_token	*list;
	char	*cmd;

	cmd = ft_strtrim(line, " ");
	list = ft_tokens(cmd);
	if (!syntax_validation(list))
	{
		printf("Error occured\n");
		rl_on_new_line();
		//exit(1);
	}
	display(list);
}

/* **************************************************** */
/*                🆁🅴🅰🅳_🅲🅾🅼🅼🅰🅽🅳                   */
/* **************************************************** */

void	ft_prompt(void)
{
	char	*command;
	while (1)
	{
		command = readline("$> ");
		ft_check(command);
		if (command_checker(command) != 0)
			break ;
		ft_lexer(command);
		free (command);
	}
}

/* **************************************************** */
/*                        🅼🅰🅸🅽                       */
/* **************************************************** */

int	main(void)
{
	ft_prompt();
	return (0);
}