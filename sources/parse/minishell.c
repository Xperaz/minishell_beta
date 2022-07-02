/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houazzan <houazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 13:56:27 by aouhadou          #+#    #+#             */
/*   Updated: 2022/07/02 15:42:34 by houazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

void display(t_command *node) {

	t_command	*tmp;
	int i;

	tmp = node;
	while (tmp)
	{
		i = 0;
		while (tmp->cmd[i])
		{
			printf("{%s} => |%d|\n", tmp->cmd[i], tmp->herdoc);
			i++;
		}
		printf(" => outfile: [%d] => infile [%d]\n", tmp->outfile, tmp->infile);
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
	free(cmd);
	return (list);
}

t_command	*parser(char *line)
{
	t_token	*list;
	t_command	*cmd_list;
	
	list = ft_lexer(line);
	if (!list)
	{
		list_clear(&list);
		return (NULL);
	}
	cmd_list = creat_cmds(list);
	if (check_dollar(cmd_list))
		expand_dollar(cmd_list);
	if (is_file2(cmd_list) != -1)
	{
		open_files(cmd_list);
		ft_remove_unsed(cmd_list);
	}
	if (!remove_quotes(cmd_list))
		print_error();
	return (cmd_list);
}

/* **************************************************** */
/*                🆁🅴🅰🅳_🅲🅾🅼🅼🅰🅽🅳                   */
/* **************************************************** */

void	ft_prompt(void)
{
	char		*command;
	t_command	*cmds;

	cmds = NULL;
	while (1)
	{
		command = readline("$> ");
		if (!command)
			ctrl_d(command);
		ft_check(command);
		if (!ft_strlen(command))
			continue;
		if (command_checker(command))
			break;
		cmds = parser(command);
		if (g_msh.syntax_err)
			execute(cmds);
	//	display(cmds);
		clear_cmds(&cmds);
		free (command);
	}
}

/* **************************************************** */
/*                        🅼🅰🅸🅽                       */
/* **************************************************** */


int	main(int ac, char **av, char **env)
{
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, handle_sig);
	ft_bzero(&g_msh, sizeof(g_msh));
	if (!g_msh.my_env)
		data_management(NULL ,ENV, env);
	ft_prompt();
	return (0);
}