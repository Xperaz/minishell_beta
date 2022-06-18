#include "../includes/minishell.h"

int	wich_redirection(char *red)
{
	int	flag;

	flag = 0;
	if ( !strncmp(red, ">>", 2))
		flag = ASO;
	else if ( !strncmp(red, "<<", 2))
		flag = HERDOC;
	else if ( !strncmp(red, ">", 1))
		flag = O_REDIRECTION;
	else if ( !strncmp(red, "<", 1))
		flag = I_REDIRECTION;
	return (flag);
}

int	check_cmd(char *tok)
{
	int	flag;

	flag = 0;
	if (tok[0] == '-')
		flag = OPTION;
	else if (!ft_strncmp(tok, "$", 1))
		flag = DOLLAR;
	return (flag);
}

void	add_flag(t_token *tmp)
{
	if (wich_redirection(tmp->data))
		tmp->key = wich_redirection(tmp->data);
	else if (check_cmd(tmp->data))
		tmp->key = check_cmd(tmp->data);
	else if (tmp->prev != NULL && !ft_strncmp(tmp->prev->data, "|", 1))
		tmp->key = COMMAND;
	else if (tmp->prev != NULL && wich_redirection(tmp->prev->data))
	{
		if (wich_redirection(tmp->prev->data) == HERDOC)
			tmp->key = DELIMTER;
		else
			tmp->key = FL;
	}
	else if (tmp->prev == NULL)
	{
		if (!strncmp(tmp->data, "<<", 2))
			tmp->key = HERDOC;
		else
			tmp->key = COMMAND;
	}
	else if (!strncmp(tmp->data, "|", 1))
		tmp->key = PIPE;
	else if (!strncmp(tmp->data, "|", 1))
		tmp->type = D_QUOTES;
	else
		tmp->key = WORD;
}

void	flag_list(t_token *list)
{
	t_token	*tmp;

	tmp = list;
	while (tmp)
	{
		add_flag(tmp);
		tmp = tmp->next;
	}
}