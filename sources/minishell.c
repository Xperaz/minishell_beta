
#include "../includes/minishell.h"

void display(t_cmd *node) {

	t_cmd	*tmp;
	int i;

	tmp = node;
	while (tmp)
	{
		i = 0;
		while (tmp->cmd[i])
		{
			printf("{%s} => |%d|", tmp->cmd[i], tmp->herdoc);
			
			i++;
		}
		if (node->herdoc)
		{
			i = 0;
		printf("\n");
		while (tmp->delims[i])
		{
			printf("|%s|", tmp->delims[i]);
			i++;
		}
		}
   		tmp = tmp->next;
		printf("\n");
	}
}

/*                        file opens                    */


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
	cmd_list = creat_cmds(list);
	expand_dollar(cmd_list);
	remove_quotes(cmd_list);
	open_files(cmd_list);
	// if (cmd_list->herdoc == 1)
	// 	cmd_list->delims = ft_split(cmd_list->del, ' ');
	display(cmd_list);
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