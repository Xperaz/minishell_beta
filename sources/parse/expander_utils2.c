/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 10:08:19 by aouhadou          #+#    #+#             */
/*   Updated: 2022/07/01 22:30:15 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ex_free(char *sub, char **ptr)
{
	free(sub);
	free_tab(ptr);
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
	t_env *ptr;

	ptr = g_msh.dup_envp;
	while(ptr)
    {
		if (!ft_strcmp1(env, ft_strndup(ptr->key, ft_strlen(ptr->key) - 1)))
			return (ft_strdup(ptr->value));
        ptr = ptr->next;
    }
	return (NULL);
}

void	fill_tab(char **ptr, char **dest)
{
	char	*val;
	int		j;
	
	remove_all_chars(*dest, '$');
	j = 0;
	while (ptr[j])
	{
		val = get_env1(ptr[j]);
		if (!val)
			replace_sub(dest, ptr[j], "");
		j++;
	}
	j = 0;
	while (ptr[j])
	{
		val = get_env1(ptr[j]);
		if (val)
			replace_sub(dest, ptr[j], val);
		j++;
	}
	free(val);
}

void	ft_break(int *flag, char *sub)
{
	*flag = 0;
	free(sub);
}
