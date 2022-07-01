/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utiles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houazzan <houazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:45:18 by houazzan          #+#    #+#             */
/*   Updated: 2022/06/30 21:46:22 by houazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../includes/minishell.h"

/* **************************************************** */
/*                                                      */
/* **************************************************** */

void	get_path()
{
	int i = 0;
	g_msh.separ_path = NULL;
	t_env *ptr;
	ptr = g_msh.dup_envp;
	while(ptr)
	{
		if (ft_strncmp(ptr->key, "PATH=", 5) == 0)
		{
			g_msh.separ_path = ft_split(ptr->value, ':');
			break ;
		}
		ptr = ptr->next;
	}
	if (g_msh.separ_path == NULL)
		g_msh.separ_path = ft_split(_PATH_STDPATH, ':');
	while(g_msh.separ_path[i])
	{
		g_msh.separ_path[i] = ft_strjoin(g_msh.separ_path[i], "/");
		i++;
	}
}

/* **************************************************** */
/*                                                      */
/* **************************************************** */

void	allocating()
{
	g_msh.cmd = (t_command *)malloc(sizeof(t_command));
	g_msh.token = (t_token *)malloc(sizeof(t_token));
	g_msh.dup_envp = (t_env *)malloc(sizeof(t_env));
    if (!g_msh.cmd || !g_msh.token || !g_msh.dup_envp)
        quit_minishell(errno, "Cannot allocate memory");
}

/* **************************************************** */
/*                                                      */
/* **************************************************** */

void  data_management(t_command *cmds, int decission, char **env)
{
	g_msh.her_signal = -1;
	if (decission == ENV)
	{
		allocating();
		get_env(env); // ^ for g_msh.dup_envp
		get_path(); // ^ for g_msh.separ_path
	}
	else
	{
		g_msh.cmd = cmds;
		env_list_to_array(); // ^ this one is for g_msh.my_env
		catagorize();
	}
}