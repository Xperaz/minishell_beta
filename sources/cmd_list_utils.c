/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 13:55:51 by aouhadou          #+#    #+#             */
/*   Updated: 2022/06/27 15:50:00 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_command	*last_cmd(t_command *token)
{
	t_command	*last;

	last = NULL;
	if (token)
	{
		last = token;
		while (last && last->next)
			last = last->next;
	}
	return (last);
}

t_command	*new_cmd_token(char **data)
{
	t_command	*new;

	new = (t_command *)malloc(sizeof(t_command));
	if (!new)
		return (NULL);
	new->cmd = data;
	new->next = NULL;
	return (new);
}

void	add_cmd_to_end(t_command **command, char **new_data)
{
	t_command	*new_node;
	t_command	*last;

	new_node = (t_command *) malloc(sizeof(t_command));
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

void	delete_cmd(t_command **head, t_command *del_node)
{
	if (*head == NULL || del_node == NULL)
		return ;
	if (*head == del_node)
		*head = del_node->next;
	free(del_node);
}

void	clear_cmds(t_command **head_ref)
{
	t_command	*temp;
	t_command	*next;

	temp = *head_ref;
	while (temp != NULL)
	{
		next = temp->next;
		delete_cmd(head_ref, temp);
		temp = next;
	}
}
