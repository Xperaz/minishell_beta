// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   unset.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: houazzan <houazzan@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/06/11 13:14:52 by houazzan          #+#    #+#             */
// /*   Updated: 2022/06/13 10:54:53 by houazzan         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../../../includes/minishell.h"

int	first_variable(char *to_remove)
{
	t_env *ptr_del;
	t_env *ptr;
	ptr = g_msh.dup_envp;
	if (ft_strcmp(ft_strtrim(ptr->key, "="), to_remove) == 0)
	{
		ptr_del = ptr;
		ptr = ptr->next;
		if(ptr_del->value)
			free(ptr_del->value);
		free(ptr_del->key);
		free(ptr_del);
		return (0);
	}
	g_msh.dup_envp = ptr;
	return(1);
}


/* **************************************************** */
/*                                                      */
/* **************************************************** */

int      remove_variable(char *to_remove)
{
	t_env *ptr_del;
	t_env *ptr;

	ptr = g_msh.dup_envp;
	if (ptr == NULL)
		return (0);
	if (first_variable(to_remove) == 0)
		return (0);
	while(ptr != NULL)
	{
		if ((ptr->next) && ft_strcmp(ft_strtrim(ptr->next->key, "="), to_remove) == 0)
		{
			ptr_del = ptr->next;
			if (ptr->next->next != NULL)
				ptr->next = ptr->next->next;
			else
				ptr->next = NULL;
			if(ptr_del->value)
				free(ptr_del->value);
			free(ptr_del->key);
			free(ptr_del);
		}
		ptr = ptr->next;
	}
	return (0);
}


/* **************************************************** */
/*                                                      */
/* **************************************************** */


int    unset()
{
	int i;
	int j;

	i = 1;
	while (g_msh.cmd->cmd[i] != NULL)
	{
		j = 0;
		while (g_msh.cmd->cmd[i][j])
		{
			if (!ft_isalnum(g_msh.cmd->cmd[i][j]) && g_msh.cmd->cmd[i][j] != '_')
			{
				printf("unset: %s : not a valid identifier \n", g_msh.cmd->cmd[i]);
				break ;
			}
			j++;
		}
		remove_variable(g_msh.cmd->cmd[i]);      
		i++;
	 }
	return(0);
}

