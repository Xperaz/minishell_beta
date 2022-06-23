
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
			printf("{%s} ", tmp->cmd[i]);
			i++;
		}
   		tmp = tmp->next;
		printf("\n");
	}
}

/*                        file opens                    */

void	ft_free(char *s1, char *s2)
{
	ft_bzero(s1, ft_strlen(s1));
	ft_bzero(s2, ft_strlen(s2));
}

int	open_redirect_input(char *file, t_cmd *node)
{
	int	fd;
	int	flag;

	flag = 1;
	if ((access(file, F_OK)) == 0)
	{
		fd = open(file, O_WRONLY,  S_IRWXU);
		node->infile = fd;
	}
	else
	{
		flag = 0;
		printf("%s: No such file or directory\n", file);
		rl_on_new_line();
	}
	return (flag);
}

void	open_app_redirect_out(char *file, t_cmd *node)
{
	int fd;

	if ((!access(file, F_OK)) == 0)
	{
		fd = open(file, O_WRONLY,  S_IWUSR);
		node->infile = fd;
	}
	else
	{
		fd = open(file, O_CREAT,  S_IWUSR);
		node->infile = fd;
	}
}

void	open_redirect_out(char *fl, t_cmd *node)
{
	int fd;

	fd = open(fl, O_CREAT, S_IRWXU);
	node->infile = fd;
}

void	ft_open(t_cmd *node)
{
	int i;

	i = -1;
	while (node->cmd[++i])
	{
		if (!ft_strncmp(node->cmd[i], ">", 1))
		{
			open_redirect_out(node->cmd[i + 1], node);
			ft_free(node->cmd[i + 1], node->cmd[i]);
		}
		else if (!ft_strncmp(node->cmd[i], ">>", 2))
		{
			open_app_redirect_out(node->cmd[i + 1], node);
			ft_free(node->cmd[i + 1], node->cmd[i]);
		}
		else if (!ft_strncmp(node->cmd[i], "<", 1))
		{
			if (!open_redirect_input(node->cmd[i + 1], node))
				break;
			ft_free(node->cmd[i + 1], node->cmd[i]);
		}
	}
}

void	open_files(t_cmd *node)
{
	node->infile = 0;
	node->outfile = 1;
	while (node)
	{
		ft_open(node);
		node = node->next;
	}
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
	cmd_list = creat_cmds(list);
	expand_dollar(cmd_list);
	open_files(cmd_list);
	remove_quotes(cmd_list);
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