/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houazzan <houazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:23:29 by houazzan          #+#    #+#             */
/*   Updated: 2022/06/28 18:28:07 by houazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../includes/minishell.h"

/* **************************************************** */
/*                       🅴🅽🆅                          */
/* **************************************************** */

int	tab_len(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	sort()
{
	int 	i;
	int		j;
	char	*temp;
   
	j = 0;
	while (g_msh.sort_env[i] != NULL)
	{
		j = i + 1;
		while (g_msh.sort_env[j] != NULL)
		{
			if (ft_strcmp(g_msh.sort_env[i], g_msh.sort_env[j]) > 0)
			{
				temp =  g_msh.sort_env[i];
				g_msh.sort_env[i] = g_msh.sort_env[j];
				g_msh.sort_env[j] = temp;
			}
			j++;
		}
		i++;
	}
}

/* **************************************************** */
/*                       🅴🅽🆅                          */
/* **************************************************** */

void	export_env()
{
    t_env   *ptr;
	int		i;
	
	i = 0;
	ptr = g_msh.dup_envp;
	sort();
	while(g_msh.sort_env[i])
	{
		printf("%s", "declare -x ");
		ptr = g_msh.dup_envp;
		while (ptr)
		{
			if (ft_strcmp(ptr->key, g_msh.sort_env[i]) == 0)
			{
				if (ft_strchr(ptr->key, '='))
					printf("%s\"%s\"\n", ptr->key, ptr->value);  
				else
					printf("%s\n", ptr->key);
			}
			ptr = ptr->next;
		}
		i++;
	}
}

/* **************************************************** */
/*                       🅴🅽🆅                          */
/* **************************************************** */
int    env(int state)
{
    t_env *ptr;

    ptr = g_msh.dup_envp;
	if (state == ADD_FUTERS)
		export_env();
	else
		while (ptr!= NULL)
		{
			if (ft_strcmp(ptr->value, "\0"))
			{
				if (ft_strlen(ft_strchr(ptr->value, '=')) == 1)
				{
					printf("%s", ptr->key);
					printf("%s\n", ptr->value);
				}
				else
				{
					printf("%s", ptr->key);
					printf("%s\n", ptr->value);
				}
			}
			ptr= ptr->next;
		}
		return (EXIT_SUCCESS);
}
