 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houazzan <houazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:49:09 by houazzan          #+#    #+#             */
/*   Updated: 2022/06/06 14:01:54 by houazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../includes/minishell.h"


int	loop_over_env(int  add_to, char **table)
{
	t_env *ptr;

	ptr = g_msh.dup_envp;
	while (ptr != NULL)
	{
		if (ft_strncmp(table[0], ptr->key, ft_strlen(table[0])) == 0)
		{
			if (table[0] == 0 && add_to == 0)
				break ;
			if (add_to == 1)
				ptr->value = ft_strjoin(ptr->value, table[1]);
			else
				ptr->value = ft_strdup(table[1]);
			return(1);
		}
		ptr = ptr->next;
	}
	return(0);
}



int already_exist(char **table)
{
	int add_to;

	add_to = 0;
	if (ft_strchr(table[0], '+'))
	{
		table[0] = ft_strtrim(table[0], "+");
		add_to = 1;
	}
	if (!loop_over_env(add_to, table))
		return(1);
	return (0);
}

/* **************************************************** */
/*                  🅸🅽🆅🅰🅻🅸🅳_🆅🅽                    */
/* **************************************************** */

void	invalid_vn(char	*table)
{
	int i;
	
	i = 1;
	// if (table[0] == 0)
	// 	table[0] = '=';
	if (ft_strlen(ft_strchr(table, '+')) >  1 || !ft_isalpha(table[0]) && table[0] != '_')
		quit_minishell(EXIT_FAILURE, ft_strjoin(ft_strjoin("export ", table)," : not a valid identifier"));
	while (table[i])
	{
		if (!ft_isdigit(table[i]) && !ft_isalpha(table[i]) && table[i] != '_' && table[i] != '+')
			quit_minishell(EXIT_FAILURE, ft_strjoin(ft_strjoin("export ", table),": not a valid identifier"));
		i++;
	}
}


/* **************************************************** */
/*                 🅴🆇🅿🅾🆁🆃_🆅🅽🅰🅼🅴                  */
/* **************************************************** */


int	export_vname()
{
	char 	**table;
	t_env 	*node;
	int 	i;

	i = 1;
	while (g_msh.cmd->cmd[i] != NULL)
	{
		table = ft_fo_split(g_msh.cmd->cmd[i], '=');
		printf("%s\n", table[1]);
		invalid_vn(table[0]);
		if (already_exist(table))
		{
			node = create_env_node(table);
			add_env_back(&g_msh.dup_envp, node);
		}
		free(table);
		i++;
	}
	return (0);
}

/* **************************************************** */
/*                    🅴🆇🅿🅾🆁🆃                        */
/* **************************************************** */

int	export()
{
	if (g_msh.cmd->cmd[1] == NULL)
		env(ADD_FUTERS);
	else
		if (export_vname())
			quit_minishell(EXIT_FAILURE, "variable name undefined");
	//data_management(NULL, NO_ENV, NULL);
	return (EXIT_SUCCESS);
}


 
 
