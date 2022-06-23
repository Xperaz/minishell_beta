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
	while (node->cmd[++i])
	{
		if ((!ft_strncmp(node->cmd[i], ">", 1)) || (!ft_strncmp(node->cmd[i], ">>", 2)))
			ft_input_file(node, &i);
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
	int	flag;

	node->infile = 0;
	node->outfile = 1;
	while (node)
	{
		flag = ft_open(node);
		if (flag >= 0)
		{
			while (node->cmd[flag])
			{
				ft_bzero(node->cmd[flag], ft_strlen(node->cmd[flag]));
				flag++;
			}
		}
		node = node->next;
	}
}