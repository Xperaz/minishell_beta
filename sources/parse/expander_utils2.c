/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 10:08:19 by aouhadou          #+#    #+#             */
/*   Updated: 2022/07/01 12:00:29 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ex_free(char *sub, char *env)
{
	free(sub);
	free(env);
}

void	ft_expand(char **dest, char *sub, char *env)
{
	if (getenv(env))
		replace_sub(dest, sub, getenv(env));
	else if (!getenv(env))
		replace_sub(dest, sub, "");
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
