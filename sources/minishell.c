/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 13:56:27 by aouhadou          #+#    #+#             */
/*   Updated: 2022/06/27 16:05:46 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

void display(t_command *node) {

	t_command	*tmp;
	int i;

	tmp = node;
	while (tmp)
	{
		i = 0;
		while (tmp->cmd[i])
		{
			//if (tmp->cmd[i][0] != 0)
			printf("{%s} => |%d| => oufilefile: [%d] => infile [%d]\n", tmp->cmd[i], tmp->herdoc, tmp->outfile, tmp->infile);
			i++;
		}
		if (tmp->herdoc == 1)
		{
			i = 0;
			printf("\n *** herdoc **\n");
			while (tmp->delims[i])
			{
				printf("|%s| ", tmp->delims[i]);
				i++;
			}
		}
   		tmp = tmp->next;
		printf("\n");
	}
}

/*                         LEXER.                       */

t_token	*ft_lexer(char *line)
{
	t_token	*list;
	char	*cmd;

	cmd = ft_strtrim(line, " ");
	list = ft_tokens(cmd);
	if (!syntax_validation(list))
	{
		list_clear(&list);
		print_error();
		return (NULL);
	}
	return (list);
}

t_command	*parser(char *line)
{
	t_token	*list;
	t_command	*cmd_list;
	
	list = ft_lexer(line);
	if (!list)
		return (NULL);
	cmd_list = creat_cmds(list);
	list_clear(&list);
	expand_dollar(cmd_list);
	open_files(cmd_list);
	if (!remove_quotes(cmd_list))
	{
		clear_cmds(&cmd_list);
		print_error(list);
		return (NULL);
	}
	return (cmd_list);
}

/* **************************************************** */
/*                🆁🅴🅰🅳_🅲🅾🅼🅼🅰🅽🅳                   */
/* **************************************************** */

void	ft_prompt(void)
{
	char	*command;
	t_command	*cmds;

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
		cmds = parser(command);
		display(cmds);
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