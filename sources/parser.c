/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 13:55:23 by aouhadou          #+#    #+#             */
/*   Updated: 2022/06/25 13:55:24 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*creat_cmds(t_token *node)
{
	t_cmd	*cmds;
	int		lst_size;
	int		i;
	int		start;

	lst_size = lstsize(node);
	cmds = NULL;
	i = 0;
	start = 0;
	while (start  < lst_size)
	{
		add_cmd_to_end(&cmds, remplir_tab(node, start));
		start += count_size(node, start) + 1;
	}
	return (cmds);
}