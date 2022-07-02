/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houazzan <houazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:03:52 by houazzan          #+#    #+#             */
/*   Updated: 2022/07/01 18:42:50 by houazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	her_handle(int sig)
{
	if (sig == SIGINT)
	{
		//printf("\033[K$>\n");
		exit(0);
	}
}

void	her_doc(char *argv)
{
	int		fd;
	char	*buff;

	g_msh.fd = open("/tmp/file", O_CREAT | O_RDWR | O_TRUNC, 0666);
	while (1)
	{
		signal(SIGINT, her_handle);
		buff = readline("heredoc> ");
		if (!buff || !ft_strcmp(buff, argv))
			break ;
		// buff = buff_check(buff);
		write(g_msh.fd, buff, ft_strlen(buff));
		write(g_msh.fd, "\n", 1);
		free(buff);
	}
	g_msh.cmd->infile = open("/tmp/file", O_RDWR);
	if (g_msh.cmd->infile  < 0)
		quit_minishell(1, strerror(1));
}


void	run_her_doc()
{
	int i;
	i = 0;
	while (g_msh.cmd->delims[i])
	{
		her_doc(g_msh.cmd->delims[i]);
		i++;
	}
}