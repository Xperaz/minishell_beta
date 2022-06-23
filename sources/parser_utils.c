#include "../includes/minishell.h"

int	ft_strcmp1(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] != '\0' || s2[j] != '\0')
	{
		if (s1[i] > s2[j])
			return (s1[i] - s2[j]);
		else if (s1[i] < s2[j])
			return ((s1[i] - s2[j]));
		i++;
		j++;
	}
	return (0);
}

int	count_size(t_token	*node, int start)
{
	t_token *tmp;
	int		i;
	int		compt;

	i = 0;
	tmp = node;
	while (i < start)
	{
		tmp = tmp->next;
		i++;
	}
	compt = 0;
	while (tmp)
	{
		if(!ft_strcmp1(tmp->data, "|"))
			break;
		compt++;
		tmp = tmp->next;
	}
	return(compt);
}
char	**remplir_tab(t_token *node, int start)
{
	char	**tab;
	int		size;
	t_token	*tmp;	
	int		i;

	size = count_size(node, start);
	tab = malloc(sizeof(char *) * (size + 1));
	if(!tab)
		return(NULL);
	i = 0;
	tmp = node;
	while (i < start)
	{
		tmp = tmp->next;
		i++;
	}
	i = 0;
	while (i < size)
	{
		tab[i] = ft_strdup(tmp->data);
		i++;
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return(tab);
}

void	remove_quotes(t_cmd *node)
{
	int	i;

	while (node)
	{
		i = 0;
		while (node->cmd[i])
		{
			if (is_quotes(node->cmd[i]))
				remove_all_chars(node->cmd[i], is_quotes(node->cmd[i]));
			i++;
		}
		node = node->next;
	}
}