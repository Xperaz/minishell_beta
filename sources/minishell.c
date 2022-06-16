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
    while (tmp)
	{
		printf("{%s} => {%d}\n", tmp->data, tmp->key);
   		tmp = tmp->next;
	}
  printf("\n");
}


/* **************************************************** */
/*                     SYNTAX_ANALYZER.                 */
/* **************************************************** */

// int		check_operator(t_token *list)
// {
// 	t_token	*tmp;
// 	int		i;

// 	i = 0;
// 	tmp = list;
// 	while (tmp)
// 	{
// 		if (is_operator(tmp->data))
// 			i++;
// 		tmp = tmp->next;
// 	}
// 	return (i);
// }

// void	parser(t_token *tokens)
// {
// 	t_token	*tmp;
// 	t_cmd	*list;
// 	int		len;

// 	len = lstsize(tokens);
// 	printf("{%d} {%d}\n", len, check_operator(tokens));
// }

/*                         LEXER.                       */
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
	}
	// parser(list);
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