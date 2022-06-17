#include "../includes/minishell.h"

void	ft_dollar(t_token **list, char *tok)
{
	int		len;
	int		i;
	char	*dollar;
	char	*rest;

	len = 0;
	while (!ft_isspace(tok[len]))
		len++;
	dollar = (char *)malloc((len + 1) * sizeof(char));
	i = -1;
	while (++i < len)
		dollar[i] = tok[i];
	dollar[i] = '\0';
	add_to_end(list, dollar); 
	if (i < ft_strlen(tok))
	{
		rest = malloc(((ft_strlen(tok) - len) + 1) * sizeof(char));
		i = 0;
		while (i < ft_strlen(tok))
			rest[i++] = tok[len++];
		rest[i] = '\0';
		add_to_end(list, rest);
	}
}

int	is_dollar(char *tok)
{
	int	i;

	i = 0;
	while (tok[i])
	{
		if (tok[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

int	have_space(char *tok)
{
	int i;

	i = 0;
	while (tok[i])
	{
		if (ft_isspace(tok[i]))
			return (1);
		i++;
	}
	return (0);
}