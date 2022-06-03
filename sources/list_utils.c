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

void	add_to_end(t_token** head, char *data)
{
	t_token*	newNode;
	t_token*	temp;

	newNode = (t_token*)malloc(sizeof(t_token));
	newNode->data = data;
	newNode->next = NULL;
	temp = *head;
	if (*head == NULL)
	{
		newNode->prev = NULL;
		*head = newNode;
		return;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = newNode;
	newNode->prev = temp;
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