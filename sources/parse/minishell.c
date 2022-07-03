/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 13:56:27 by aouhadou          #+#    #+#             */
/*   Updated: 2022/07/03 23:26:57 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"
#include "termios.h"

void display(t_command *node) {

	t_command	*tmp;
	int i;

	tmp = node;
	while (tmp)
	{
		i = 0;
		while (tmp->cmd[i])
		{
			printf("{%s} => |%d| ==> |i = %d\n|", tmp->cmd[i], tmp->herdoc, i);
			i++;
		}
		printf(" => outfile: [%d] => infile [%d]\n", tmp->outfile, tmp->infile);
		// if (tmp->herdoc == 1)
		// {
		// 	i = 0;
		// 	printf("\n *** herdoc **\n");
		// 	while (tmp->delims[i])
		// 	{
		// 		printf("|%s| ", tmp->delims[i]);
		// 		i++;
		// 	}
		// }
   		tmp = tmp->next;
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
			rl_on_new_line();
		cmds = parser(command);
		// display(cmds);
		 if (g_msh.syntax_err && cmds)
			 execute(cmds);
		clear_cmds(&cmds);
		free (command);
	}
}


void	hide_ctl()
{
	 struct termios attributes;

    tcgetattr(STDIN_FILENO, &attributes);
    attributes.c_lflag &= ~ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);
}

void	show_ctl()
{
	 struct termios attributes;

    tcgetattr(STDIN_FILENO, &attributes);
    attributes.c_lflag |= ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);
}

/* **************************************************** */
/*                        🅼🅰🅸🅽                       */
/* **************************************************** */


int	main(int ac, char **av, char **env)
{
	g_msh.signal = 0;
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, SIG_IGN);
	hide_ctl();
	ft_bzero(&g_msh, sizeof(g_msh));
	if (!g_msh.my_env)
		data_management(NULL ,ENV, env);
	ft_prompt();
	show_ctl();
	return (0);
}