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


int      remove_variable(char *remove)
{
	t_env *ptr_del;
	t_env *ptr;

	ptr = g_msh.dup_envp;
	if (ptr == NULL)
		return (0);
	while(ptr != NULL)
	{
		if ((ptr->next) && ft_strcmp(ptr->next->key, remove) == 0)
		{
			printf("here\n");
			ptr_del = ptr->next;
			if (ptr->next->next != NULL)
				ptr = ptr->next->next;
			else
				ptr->next = NULL;
			free(ptr_del);
		}
		ptr = ptr->next;
	}
	return (0);
}

int    unset()
{
	int i;
	int j;

	i = 1;
	
	while (g_msh.cmd->cmd[i] != NULL)
	{
		j = 0;
		while (g_msh.cmd->cmd[j])
		{
			if (!ft_isalnum(g_msh.cmd->cmd[i][j]) && g_msh.cmd->cmd[i][j] != '_')
				quit_minishell(EXIT_FAILURE, ft_strjoin(ft_strjoin("unset: ", g_msh.cmd->cmd[i]), ": not a valid identifier"));
			i++;
		}
		remove_variable(g_msh.cmd->cmd[i]);      
		i++;
	 }
	return(0);
}

