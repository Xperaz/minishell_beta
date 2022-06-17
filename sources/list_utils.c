#include "../includes/minishell.h"

void add_front(t_token** head, char *data)
{
	t_token*	newNode;
	
	newNode = (t_token*)malloc(sizeof(t_token));
	newNode->data = data;
	newNode->next = (*head);
	newNode->prev = NULL;
	if ((*head) != NULL)
		(*head)->prev = newNode;
	(*head) = newNode;
}

void	add_to_end(t_token** head_ref, char *data)
{
    t_token* new_node;
    t_token* last;

	new_node = (t_token*)malloc(sizeof(t_token));
	last = *head_ref;
    new_node->data = data;
    new_node->next = NULL;
    if (*head_ref == NULL) {
        new_node->prev = NULL;
        *head_ref = new_node;
        return;
    }
    while (last->next != NULL)
        last = last->next;
    last->next = new_node;
    new_node->prev = last;
    return;
}

void	delete_node(t_token** head, t_token *del_node)
{
	if (*head == NULL || del_node == NULL)
		return;
	if (*head == del_node)
		*head = del_node->next;
	if (del_node->next != NULL)
		del_node->next->prev = del_node->prev;
	if (del_node->prev != NULL)
		del_node->prev->next = del_node->next;
	free(del_node);
}

void	list_clear(t_token** head_ref)
{
	t_token* temp;
	t_token* next;
	
	temp = *head_ref;
	while (temp != NULL)
	{
		next = temp->next;
		delete_node(head_ref, temp);
		temp = next;
	}
}

int	lstsize(t_token *lst)
{
	int		i;
	t_token	*new;

	new = lst;
	i = 0;
	while (new != NULL)
	{
		i++;
		new = new->next;
	}
	return (i);
}