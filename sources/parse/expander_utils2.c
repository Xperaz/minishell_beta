/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 10:08:19 by aouhadou          #+#    #+#             */
/*   Updated: 2022/07/03 23:26:42 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ex_free(t_dinfo info)
{
	if (info.flag == 3)
	{
		free(info.sub);
		free_tab(info.ptr);
	}
	else
		free(info.sub);
}

int	check_dollar(t_command	*list)
{
	t_command	*tmp;
	int			i;

	tmp = list;
	while (tmp)
	{
		i = 0;
		while (tmp->cmd[i])
		{
			if (is_dollar(tmp->cmd[i]) != -1)
				return (1);
			i++;
		}
		tmp = tmp->next;
	}
	return (0);
}

char	*get_env1(char *env)
{	
	t_env	*ptr;

	ptr = g_msh.dup_envp;
	while (ptr)
	{
		if (!ft_strcmp1(env, ft_strndup(ptr->key, ft_strlen(ptr->key) - 1)))
			return (ft_strdup(ptr->value));
		ptr = ptr->next;
	}
	return (NULL);
}

void	fill_tab(char **ptr, char **dest)
{
	char	*array;
	int		j;

	j = -1;
	while (ptr[++j])
	{
		array = ft_strdup(ptr[j]);
		ft_memmove(array + 1, array, ft_strlen(array) + 1);
		array[0] = '$';
		if (!get_env1(ptr[j]))
			replace_sub(dest, array, "");
		free(array);
	}
	j = -1;
	while (ptr[++j])
	{
		array = ft_strdup(ptr[j]);
		ft_memmove(array + 1, array, ft_strlen(array) + 1);
		array[0] = '$';
		if (get_env1(ptr[j]))
			replace_sub(dest, array, get_env1(ptr[j]));
		free(array);
	}
}

void	ft_break(int *flag, char *sub)
{
	*flag = 0;
	free(sub);
}
