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

void    add_cmd_to_end(t_cmd** command, char **new_data)
{
    t_cmd   *new_node; 
    t_cmd   *last;
    
    new_node = (t_cmd *) malloc(sizeof(t_cmd));
    new_node->cmd = new_data;
    new_node->next = NULL;
  
    if (*command == NULL)
    {
       *command = new_node;
       return;
    } 
    
    last = *command;
    while (last->next != NULL)
        last = last->next;
    last->next = new_node;
    return;   
}