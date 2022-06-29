# Minishell

void	ft_remove_unsed(t_command *node)
{
	int 	count;
	int		total;
	char	**tab;
	int		i;
	int		j;
	t_command	*tmp;

	tmp = node;
	while (tmp)
	{
		total = count_tab(tmp->cmd);
		count = count_unsed(tmp->cmd);
		tab = (char **)malloc(((total - count) + 1) * sizeof(char *));
		i = 0;
		j = 0;
		while (tmp->cmd[i])
		{
			if (tmp->cmd[j][0] != 0)
			{
				tab[j] = ft_strdup(tmp->cmd[i]);
				j++;
			}
			i++;
		}
		tab[j] = NULL;
		int k = 0;
		while (tab[k])
			printf("{%s}\n", tab[k++]);
		tmp->cmd = tab;
		tmp = tmp->next;
	}
}