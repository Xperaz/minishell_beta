/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houazzan <houazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:08:16 by houazzan          #+#    #+#             */
/*   Updated: 2022/07/02 15:35:02 by houazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	special_futers_for_cmd()
{
	t_env *ptr;
	
	if(ft_strcmp(g_msh.cmd->cmd[0], "./minishell") == 0)
	{
		ft_putstr_fd(g_msh.cmd->cmd[0], 2);
		while (ptr)
		{
			if (ft_strcmp(ptr->key, "SHLVL=") == 0)
				ptr->value = ft_itoa(ft_atoi(ptr->value) + 1);
			ptr = ptr->next;
		}
	}
	
}



int	state(char *input)
{
	struct stat buff;
	if (stat(input, &buff))
		return(0);
	if (!S_ISREG(buff.st_mode) &&  S_ISDIR(buff.st_mode))
		return(1);
	return(0);
}

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
		if(access(g_msh.cmd->cmd[0], F_OK) == 0)
			command = g_msh.cmd->cmd[0];
		else
			command = ft_strjoin(g_msh.separ_path[i], g_msh.cmd->cmd[0]);
		if (access(command, F_OK) == 0)
			break;
		i++;
	}
	if (access(command, F_OK) == 0)
		execve(command, g_msh.cmd->cmd, g_msh.my_env);
	if (state(command))
		quit_minishell(126, ft_strjoin(ft_strjoin("bash: ", command), " is a directory"));
	else
	 	quit_minishell(127, ft_strjoin(ft_strjoin("bash: ", command), " commaned not found"));
	exit(1);
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
	int status = 0;
	set_pipes();
	while (g_msh.cmd)
	{
		if (g_msh.cmd->cmd_type == EXECVE || g_msh.cmd->next || g_msh.cmd_number > 1 || g_msh.cmd->herdoc)
		{
			g_msh.pid = fork();			
			if (g_msh.pid == 0)
			{
				
				if (g_msh.cmd->herdoc != 0)
					run_her_doc();
				// if (command != 0)
				// 	dup2(g_msh.pipefd[(command - 1) * 2], STDIN_FILENO);
				// if (command != g_msh.cmd_number - 1)
				// 	dup2(g_msh.pipefd[command * 2 + 1], STDOUT_FILENO);
				if (g_msh.cmd->outfile != 1)
				{
					ft_putstr_fd("hello\n", 2);
					dup2(g_msh.cmd->outfile, STDOUT_FILENO);
				}
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
	waitpid(g_msh.pid, (int *)&g_msh.exit_status, 0);
	if ( WIFEXITED(g_msh.exit_status) )
		g_msh.exit_status =  WEXITSTATUS(g_msh.exit_status);    
}


/* **************************************************** */
/*                        🅼🅰🅸🅽                       */
/* **************************************************** */

void	execute(t_command *cmds)
{
	g_msh.pipe_id = 0;
	data_management(cmds ,NO_ENV, NULL);
	execute_cmd();
	data_management(cmds ,NO_ENV, NULL);
	int i = 0;
	g_msh.cmd_number = 0;
	//return (0);
}
