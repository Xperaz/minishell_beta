#include "../includes/minishell.h"

void	ft_free(char *s1, char *s2)
{
	ft_bzero(s1, ft_strlen(s1));
	ft_bzero(s2, ft_strlen(s2));
}

int ft_open(t_cmd *node)
{
	int i;
	int	flag;

	i = -1;
	flag = 1;
	node->del = NULL;
	while (node->cmd[++i])
	{
		if ((!ft_strncmp(node->cmd[i], ">", 1)) || (!ft_strncmp(node->cmd[i], ">>", 2)))
			ft_input_file(node, &i);
		else if (!ft_strncmp(node->cmd[i], "<<", 2))
			create_delimters(node, &i);
		else if (!ft_strncmp(node->cmd[i], "<", 1))
		{
			if (!open_redirect_input(node->cmd[i + 1], node))
			{
				ft_bzero(node->cmd[i], ft_strlen(node->cmd[i]));
				return (i + 2);
			}
			ft_free(node->cmd[i + 1], node->cmd[i]);
		}
	}
	return(-1);
}

void	open_files(t_cmd *node)
{
	int		flag;
	t_cmd	*tmp;

	node->infile = 0;
	node->outfile = 1;
	node->herdoc = 	0;
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
	if (!ft_strncmp(tok, ">", 1) || !ft_strncmp(tok, "<", 1)
			|| !ft_strncmp(tok, ">>", 2) || !ft_strncmp(tok, "<<", 2))
			return (1);
	return (0);	
}

int	is_file(t_cmd *node)
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
	return (i);
}