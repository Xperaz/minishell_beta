/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utiles2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houazzan <houazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:08:13 by houazzan          #+#    #+#             */
/*   Updated: 2022/06/28 18:24:42 by houazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../includes/minishell.h"


void	env_list_to_array()
{
	int i;
	int count;
	t_env *ptr;

	i = 0;
	ptr = g_msh.dup_envp;
	count = ft_env_size(ptr);
	
	g_msh.my_env = (char **) ft_calloc(count + 1, sizeof(char *));
	g_msh.sort_env = (char **) ft_calloc(count + 1, sizeof(char *));
	while(ptr)
	{
		g_msh.my_env[i] = ft_strdup(ft_strjoin(ptr->key, ptr->value));
		g_msh.sort_env[i] = ft_strdup(ptr->key);
		ptr = ptr->next;
		i++;
	}
}


/* **************************************************** */
/*               🅰🅻🆁🅴🅰🅳🆈_🆃🅷🅴🆁🅴                  */
/* **************************************************** */

int	already_there(t_env **head)
{
	t_env *ptr;

	ptr = *(head);
	while (ptr != NULL)
	{
		if(ft_strcmp(ptr->key, "OLDPWD=") == 0)
			return(1);
		ptr = ptr->next;
	}
	return(0);
}

/* **************************************************** */
/*                   🅲🆁🅴🅰🆃🅴_🅽🅾🅳🅴                  */
/* **************************************************** */
t_env	*create_env_node(char **env)
{
	t_env	*new_node;

	if (!env[1])
		env[1] = ft_strdup("");
	new_node = (t_env *)malloc(sizeof(t_env));
	new_node->key = ft_strdup(ft_strjoin(env[0], "="));
	new_node->value = ft_strdup(env[1]);
	new_node->next = NULL;
	return (new_node);
}

/* **************************************************** */
/*                   🅰🅳🅳_🅴🅽🆅_🅱🅰🅲🅺                */
/* **************************************************** */

void	add_env_back(t_env **head, t_env *new_node)
{
	t_env	*last_node;

	if (*head == NULL)
		*head = new_node;
	else
	{
		last_node = (*head);
		while (last_node->next != NULL)
			last_node = last_node->next;
		last_node->next = new_node;
	}
}

/* **************************************************** */
/*                      🅶🅴🆃_🅴🅽🆅                    */
/* **************************************************** */

void	get_env(char **env)
{
	t_env	*node;
	int		i;
	
	i = 0;
	g_msh.dup_envp = NULL;
	while (env[i])
	{
		node = create_env_node(ft_sp_split(env[i], '='));
		add_env_back(&g_msh.dup_envp, node);
		i++;
	}
	if (!already_there(&g_msh.dup_envp))
	{
		node = create_env_node(ft_split("OLDPWD", ' '));
		node->key = ft_strtrim(node->key, "=");
		add_env_back(&g_msh.dup_envp, node);
	}
}

