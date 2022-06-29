/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houazzan <houazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 13:55:23 by aouhadou          #+#    #+#             */
/*   Updated: 2022/06/28 10:51:22 by houazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strcmp1(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] != '\0' || s2[j] != '\0')
	{
		if (s1[i] > s2[j])
			return (s1[i] - s2[j]);
		else if (s1[i] < s2[j])
			return ((s1[i] - s2[j]));
		i++;
		j++;
	}
	return (0);
}

t_command	*creat_cmds(t_token *node)
{
	t_command	*cmds;
	int			lst_size;
	int			i;
	int			start;

	lst_size = lstsize(node);
	cmds = NULL;
	i = 0;
	start = 0;
	while (start < lst_size)
	{
		add_cmd_to_end(&cmds, remplir_tab(node, start));
		start += count_size(node, start) + 1;
	}
	return (cmds);
}
