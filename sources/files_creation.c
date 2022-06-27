/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 13:56:13 by aouhadou          #+#    #+#             */
/*   Updated: 2022/06/27 15:54:18 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_outfile(char *file)
{
	if ((!ft_strcmp1(file, ">")) || (!ft_strcmp1(file, ">>"))
		|| (!ft_strcmp1(file, "<>")))
		return (1);
	return (0);
}

int	ft_open(t_command *node)
{
	int	i;

	i = -1;
	node->del = NULL;
	while (node->cmd[++i])
	{
		if (is_outfile(node->cmd[i]))
			ft_out_file(node, &i);
		else if (!ft_strcmp1(node->cmd[i], "<<"))
			create_delimters(node, &i);
		else if (!ft_strcmp1(node->cmd[i], "<"))
		{
			if (access(node->cmd[i + 1], F_OK) && node->cmd[i - 1] == 0)
				printf("shell: no such file: %s\n", node->cmd[i + 1]);
			else if (!open_redirect_input(node->cmd[i + 1], node))
			{
				ft_bzero(node->cmd[i], ft_strlen(node->cmd[i]));
				return (i + 2);
			}
			ft_free(node->cmd[i + 1], node->cmd[i]);
		}
	}
	return (-1);
}

void	open_files(t_command *node)
{
	int			flag;
	t_command	*tmp;

	node->infile = 0;
	node->outfile = 1;
	node->herdoc = 0;
	tmp = node;
	while (tmp)
	{
		flag = ft_open(tmp);
		if (flag >= 0)
		{
			while (tmp->cmd[flag])
			{
				ft_bzero(tmp->cmd[flag], ft_strlen(tmp->cmd[flag]));
				flag++;
			}
		}
		if (tmp->herdoc == 1)
			tmp->delims = ft_split(tmp->del, ' ');
		tmp = tmp->next;
	}
}

int	is_redirection(char *tok)
{
	if (!ft_strcmp1(tok, ">") || !ft_strcmp1(tok, "<")
		|| !ft_strcmp1(tok, ">>") || !ft_strcmp1(tok, "<<")
		|| !ft_strcmp1(tok, "<>"))
		return (1);
	return (0);
}

int	is_file(t_command *node)
{
	int	i;

	while (node)
	{
		i = 0;
		while (node->cmd[i])
		{
			if (is_redirection(node->cmd[i]))
				return (i);
			i++;
		}
		node = node->next;
	}
	return (0);
}
