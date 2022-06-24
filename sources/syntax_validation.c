#include "../includes/minishell.h"

int	check_is_var(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '"')
			return(34);
		if (var[i] == '\'')
			return(39);
		i++;
	}
	return (0);
}

int	invalid_token(char *node)
{
	int	i;

	i = 0;
	while (node[i])
	{
		if (node[i] == '(' || node[i] == ')')
			return (0);
		i++;
	}
	if (!ft_strncmp(node, "()", 2) || !ft_strncmp(node, "||", 2)
		|| !ft_strncmp(node, "&&", 2))
			return (0);
	return (1);
}

int	is_operator(char *tok)
{
	if (!ft_strncmp(tok, ">", 1) || !ft_strncmp(tok, "<", 1)
			|| !ft_strncmp(tok, ">>", 2) || !ft_strncmp(tok, "<<", 2)
			|| !ft_strncmp(tok, "|", 2))
			return (1);
	return (0);	
}


int		syntax_validation(t_token *list)
{
	t_token	*tmp;

	tmp = list;
	int flag = 0;
	while (tmp != NULL)
	{
		if (tmp->prev != NULL)
		{
			if (!ft_strncmp(tmp->prev->data, "env", 3) && check_is_var(tmp->data))
				remove_all_chars(tmp->data, check_is_var(tmp->data));
		}
		if (!invalid_token(tmp->data))
			return (0);
		else if (is_operator(tmp->data) &&
			(tmp->next == NULL || is_operator(tmp->next->data)))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}