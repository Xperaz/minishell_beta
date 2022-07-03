/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:03:52 by houazzan          #+#    #+#             */
/*   Updated: 2022/07/03 22:26:40 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char 	*buff_check(char *str)
{	
	int 	i;
	int		len;
	char	*sub;
	char	*env;

	i = 0;
	len = ft_strlen(str);
	while (str[++i])
	{
		if (is_dollar(str) >= 0)
		{
			sub = dollar_substr(str);
			env = dollar_substr1(str);
			if (get_env1(env))
				replace_sub(&str, sub, get_env1(env));
			else if (!get_env1(env))
				replace_sub(&str, sub, "");
			replace_sub(&str, sub, env);
		}
	}
	return(str);
}



void	her_handle(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		exit(0);
	}
}
void	her_doc(char *argv, int fd)
{
	char	*buff;
	char	*str;
	int 	len;

	g_msh.signal = 1;
	while (1)
	{
		signal(SIGINT, her_handle);
		 buff = readline("heredoc> ");
		if (!buff || !ft_strcmp(buff, argv))
			break;
		if ((str[0] != '\'' && str[len] !='\'') || (str[0] != '\"' && str[len] != '\"'))
			buff = ft_strdup (buff_check(buff));
		write(fd, buff, ft_strlen(buff));
		write(fd, "\n", 1);
		free(buff);
	}
	close(fd);
	exit (0);
}

void	run_her_doc(char **argv, int fd)
{

	int i;
	int	pid;
	i = 0;
	g_msh.signal = 5;
	pid = fork();
	if (pid == 0)
	{
		while (argv[i])
		{
			if (fd  < 0)
				quit_minishell(1, strerror(1));
			her_doc(argv[i], fd);
			i++;
		}
	}
	waitpid(pid, (int *)&g_msh.exit_status, 0);
	g_msh.signal = 0;
}