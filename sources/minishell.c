
#include "../includes/minishell.h"


void display(t_token* node) {

	t_token	*tmp;
	tmp = node;
    while (tmp)
	{
		printf("{%s} => {%d} => |%d|\n", tmp->data, tmp->key, tmp->type);
   		tmp = tmp->next;
	}
  printf("\n");
}

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
	flag_list(list);
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