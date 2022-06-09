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
/*                     get_tokens                       */
/* **************************************************** */

t_token	*ft_tokens(char *line)
{
	t_token	*list;
	char	*tok;
	int		i;

	list = NULL;
	i = -1;
	while (line[++i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (line[i] == '"' || line[i] == '\'')
			tokenize_quotes(&list, line, &i);
		else
		{
			tok = ft_normal(line, i);
			if (check_redirection(tok) >= 0)
				redirections(&list, tok, &i);
			else
				redirection1(&list, tok, line, &i);
		}
	}
	free(tok);
	return (list);
}

void	ft_lexer(char *line)
{
	t_token	*list;
	char	*cmd;

	cmd = ft_strtrim(line, " ");
	list = ft_tokens(cmd);
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