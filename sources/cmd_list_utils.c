/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 13:55:51 by aouhadou          #+#    #+#             */
/*   Updated: 2022/06/26 16:40:21 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*last_cmd(t_cmd *token)
{
	t_cmd	*last;

	last = NULL;
	if (token)
	{
		last = token;
		while (last && last->next)
			last = last->next;
	}
	return (last);
}

t_cmd	*new_cmd_token(char **data)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmd = data;
	new->next = NULL;
	return (new);
}

void	add_cmd_to_end(t_cmd **command, char **new_data)
{
	t_cmd	*new_node;
	t_cmd	*last;

	new_node = (t_cmd *) malloc(sizeof(t_cmd));
	new_node->cmd = new_data;
	new_node->next = NULL;
	if (*command == NULL)
	{
		*command = new_node;
		return ;
	}
	last = *command;
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
	return ;
}

void	delete_cmd(t_cmd **head, t_cmd *del_node)
{
	if (*head == NULL || del_node == NULL)
		return ;
	if (*head == del_node)
		*head = del_node->next;
	free(del_node);
}

void	clear_cmds(t_cmd **head_ref)
{
	t_cmd	*temp;
	t_cmd	*next;

	temp = *head_ref;
	while (temp != NULL)
	{
		next = temp->next;
		delete_cmd(head_ref, temp);
		temp = next;
	}
}
