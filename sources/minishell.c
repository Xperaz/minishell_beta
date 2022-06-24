
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

	if (line)
		cmd = ft_strtrim(line, " ");
	list = ft_tokens(cmd);
	if (!syntax_validation(list))
		print_error();
	flag_list(list);
	cmd_list = creat_cmds(list);
	expand_dollar(cmd_list);
	remove_quotes(cmd_list);
	open_files(cmd_list);
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
		if (!command)
			ctrl_d();
		ft_check(command);
		if (!ft_strlen(command))
			continue;
		if (command_checker(command))
			break;
		ft_lexer(command);
		free (command);
	}
}

/* **************************************************** */
/*                        🅼🅰🅸🅽                       */
/* **************************************************** */


int	main(void)
{
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, handle_sig);
	ft_prompt();
	return (0);
}