
#include "../includes/minishell.h"


void display(t_token* node) {

	t_token	*tmp;
	tmp = node;
    while (tmp)
	{
		printf("{%s} => {%d} => |%d|\n", tmp->data, tmp->key, tmp->dq);
   		tmp = tmp->next;
	}
  printf("\n");
}

/*                         PARSER.                      */

t_cmd	*parser(t_token	*list)
{
	t_cmd	*cmds;
	t_token	*tmp;

	tmp = list;
	cmds = NULL;
	while (tmp)
	{
		tmp = tmp->next;
	}
	return(cmds);
}

/*                         LEXER.                       */

void	ft_lexer(char *line)
{
	t_token	*list;
	char	*cmd;
	t_cmd	*cmd_list;

	cmd = ft_strtrim(line, " ");
	list = ft_tokens(cmd);
	if (!syntax_validation(list))
	{
		printf("Error occured\n");
		rl_on_new_line();
	}
	flag_list(list);
	cmd_list = parser(list);
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