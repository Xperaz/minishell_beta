/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 13:56:22 by aouhadou          #+#    #+#             */
/*   Updated: 2022/06/30 16:13:25 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*last_token(t_token *token)
{
	t_token	*last;

	last = NULL;
	if (token)
	{
		last = token;
		while (last && last->next)
			last = last->next;
	}
	return (last);
}

t_token	*new_token(char *data, int size, t_token_type type)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->data = ft_sub_str(data, size);
	new->size = size;
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	add_to_end(t_token **token, t_token *new)
{
	t_token	*tmp;

	if ((*token) && new)
	{
		tmp = last_token((*token));
		new->prev = tmp;
		tmp->next = new;
	}
	else
		(*token) = new;
	(*token)->taille++;
}

void	delete_node(t_token **head, t_token *del_node)
{
	if (*head == NULL || del_node == NULL)
		return ;
	if (*head == del_node)
		*head = del_node->next;
	if (del_node->next != NULL)
		del_node->next->prev = del_node->prev;
	if (del_node->prev != NULL)
		del_node->prev->next = del_node->next;
	free(del_node);
}

void	*free_node(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

void	list_clear(t_token	**lst)
{
	t_token	*holder;

	if (!lst)
		return ;
	while (*lst)
	{
		holder = *lst;
		*lst = (*lst)->next;
		holder->data = free_node(holder->data);
		holder = free_node(holder);
	}
	*lst = NULL;
}
