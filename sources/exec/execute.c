/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houazzan <houazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:08:16 by houazzan          #+#    #+#             */
/*   Updated: 2022/06/30 22:05:41 by houazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
 
/* **************************************************** */
/*                                                      */
/* **************************************************** */

void	command_runing()
{
	char *command;
	int i;
	
	i = 0;
	while(g_msh.separ_path[i] && g_msh.cmd->cmd[0])
	{
		command = ft_strjoin(g_msh.separ_path[i], g_msh.cmd->cmd[0]);
		if (access(command, X_OK) == 0)
			break;
		free(command);
		i++;
	}
	if(command)
		execve(command, g_msh.cmd->cmd, g_msh.my_env);
}
/* **************************************************** */
/*                                                      */
/* **************************************************** */

void	close_pipes()
{
	int	i;

	i = 0;
	while (i < 2 * (g_msh.cmd_number - 1))
	{
		close(g_msh.pipefd[i]);
		
		i++;
	}
}


/* **************************************************** */
/*                                                      */
/* **************************************************** */

void	set_pipes()
{
	int i;

	i = 0;
	if (g_msh.cmd_number > 0)
	{
		g_msh.pipefd = (int *) malloc(sizeof(int) * 2 * (g_msh.cmd_number - 1));
		if(!g_msh.pipefd)
			quit_minishell(errno, "Cannot allocate memory");
	}
	i = 0;
	while(i < g_msh.cmd_number - 1)
	{
		if(pipe(g_msh.pipefd + 2 * i) < 0)
			quit_minishell(errno, "Broken pipe");
		i++;
	}
}


/* **************************************************** */
/*                                                      */
/* **************************************************** */
void	execute_cmd()
{
	int command;

	command = 0;
	set_pipes();
	while (g_msh.cmd)
	{
		if (g_msh.cmd->herdoc != 0)
			run_her_doc();
		if (g_msh.cmd->cmd_type == EXECVE || g_msh.cmd->next || g_msh.cmd_number > 1)
		{
			g_msh.pid = fork();			
			if (g_msh.pid == 0)
			{					
				if (command != 0)
					dup2(g_msh.pipefd[(command - 1) * 2], STDIN_FILENO);
				if (command != g_msh.cmd_number - 1)
					dup2(g_msh.pipefd[command * 2 + 1], STDOUT_FILENO);
				if (g_msh.cmd->outfile != 1) 
					dup2(g_msh.cmd->outfile, STDOUT_FILENO);
				if (g_msh.cmd->infile != 0)
					dup2(g_msh.cmd->infile, STDIN_FILENO);
				close_pipes();
				command_runing();
			}
		}
		else
			run_builtins();
		command++;
		g_msh.cmd = g_msh.cmd->next;
	}
	close_pipes();
	waitpid(g_msh.pid, NULL, 0);
}

/* **************************************************** */
/*                        🅼🅰🅸🅽                       */
/* **************************************************** */

void	execute(t_command *cmds)
{
	g_msh.pipe_id = 0;
	data_management(cmds ,NO_ENV, NULL);
	execute_cmd();
	g_msh.cmd_number = 0;
	//return (0);
}
// ~ don't forget to free after every execute 
// ! don't know if i should cheak the exite status 
//! in case of using pipes.
//! the command is not found, the child process returns 127 and the parent process returns 1;
//! the command isn't executable or the command is a directory, the child process returns 126 and the parent process returns 1;
//! if i forked at the first i only need to use waitpid to rejester the exit status " "
//! at many level ./minishell SHELLLEVEL should update and also the env should be.
