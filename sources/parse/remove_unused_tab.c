#include "../../includes/minishell.h"

int	count_unsed(char **tab)
{
	int i;
	int	len;

	len = 0;
	i = 0;
	while (tab[i])
	{
		if (tab[i][0] == 0)
			len++;
		i++;
	}
	return (len);
}

int	count_tab(char **tab)
{
	int i;
	
	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	ft_remove_unsed(t_command *node)
{
	t_remove	data;
	t_command	*tmp;
	int			len;

	tmp = node;
	while (tmp)
	{
		data.total = count_tab(tmp->cmd);
		data.count = count_unsed(tmp->cmd);
		len = (data.total - data.count) + 1;
		data.tab = (char **)malloc(len * sizeof(char *));
		data.i = 0;
		data.j = 0;
		while (tmp->cmd[data.i])
		{
			if (tmp->cmd[data.i][0] != 0)
				data.tab[data.j++] = ft_strdup(tmp->cmd[data.i]);
			else
				free(tmp->cmd[data.i]);
			data.i++;
		}
		data.tab[data.j] = NULL;
		tmp->cmd = data.tab;
		tmp = tmp->next;
	}
}