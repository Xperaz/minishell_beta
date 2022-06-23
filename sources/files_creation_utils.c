#include "../includes/minishell.h"

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

int	open_redirect_input(char *file, t_cmd *node)
{
	int	fd;
	int	flag;

	flag  = 1;
	if ((access(file, F_OK)) == 0)
	{
		fd = open(file, O_WRONLY,  S_IRWXU);
		node->infile = fd;
	}
	else
		flag = 0;
	return (flag);
}

void	open_app_redirect_out(char *file, t_cmd *node)
{
	int fd;

	if ((!access(file, F_OK)) == 0)
	{
		fd = open(file, O_WRONLY,  S_IWUSR);
		node->outfile = fd;
	}
	else
	{
		fd = open(file, O_CREAT,  S_IWUSR);
		node->outfile = fd;
	}
}

void	open_redirect_out(char *fl, t_cmd *node)
{
	int fd;

	fd = open(fl, O_CREAT, S_IRWXU);
	node->outfile = fd;
}

void	ft_input_file(t_cmd *node, int *i)
{
	if (!ft_strncmp(node->cmd[*i], ">", 1))
	{
			open_redirect_out(node->cmd[*i + 1], node);
			ft_free(node->cmd[*i + 1], node->cmd[*i]);
	}
	else if (!ft_strncmp(node->cmd[*i], ">>", 2))
	{
			open_app_redirect_out(node->cmd[*i + 1], node);
			ft_free(node->cmd[*i + 1], node->cmd[*i]);
	}
}