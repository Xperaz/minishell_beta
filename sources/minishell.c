/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 13:56:27 by aouhadou          #+#    #+#             */
/*   Updated: 2022/06/25 18:27:00 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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
			printf("|%s| ", tmp->delims[i]);
			i++;
		}
		}
   		tmp = tmp->next;
		printf("\n");
	}
}

/*                        file opens                    */

// void    free_nfd(int **nfd)
// {
//     int    i;

//     i = 0;
//     while (nfd[i++])
//         free(nfd[i]);
//     free(nfd);
// }

// int    init_pipe(t_cmd *cur, int **nfd, int i)
// {
//     nfd[i] = malloc(sizeof(int) * (2));
//     if (nfd[i] == NULL)
//         return (0);
//     if (pipe(nfd[i]) == -1)
//         return (0);
//     if (i == 0)
//         cur->infile = 0;
//     else
//         cur->infile = nfd[i - 1][0];
//     if (cur->next == NULL)
//     {
//         close(nfd[i][0]);
//         close(nfd[i][1]);
//         cur->outfile = 1;
//     }
//     else
// 		cur->outfile = nfd[i][1];
//     return (0);
// }

// int    open_pipe(t_cmd *cmd, int len)
// {
//     int        **nfd;
//     t_cmd      *cur;
//     int        ret;
//     int        i;

//     i = 0;
//     cur = cmd;
//     nfd = (int **)malloc(sizeof(int) * (len + 1));
//     if (nfd == NULL)
//         return (50);
//     nfd[len] = 0;
//     while (cur)
//     {
//         ret = init_pipe(cur, nfd, i);
//         if (ret != 0)
//         {
//             free_nfd(nfd);
//             return (ret);
//         }
//         cur = cur->next;
//         i++;
//     }
//     free_nfd(nfd);
//     return (0);
// }

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
	{
		printf("*** %d ***\n", syntax_validation(list));
		print_error(list);
	}
	else
	{
		cmd_list = creat_cmds(list);
		expand_dollar(cmd_list);
		remove_quotes(cmd_list);
		//if (lstsize2(cmd_list) > 1)
			//open_pipe(cmd_list, lstsize2(cmd_list));
		open_files(cmd_list);
		display(cmd_list);
	}
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