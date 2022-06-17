#include "../includes/minishell.h"

int		check_redirection(char *tok)
{
	int	i;

	i = 0;
	while (tok[i])
	{
		if (tok[i] == '>' || tok[i] == '<')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_redirection(char *tok, int n)
{
	char	*res;
	int		i;
	int		j;
	int		start;

	i = 0;
	start = n;
	while (tok[n] == '>' || tok[n] == '<')
	{
		n++;
		i++;
	}
	res = malloc((i + 1) * sizeof(char));
	j = 0;
	res[i] = '\0';
	while (j < i)
		res[j++] = tok[start++];
	return (res);
}

void	redirection1(t_token **list, char *tok, char *line, int *i)
{
	char	*ptr;

	ptr = ft_normal(line, *i + 1);
	add_to_end(list, tok);
	*i += ft_strlen(ptr);
}

void	redirections(t_token **list, char *tok, int *i)
{
	int		pos;
	char	*ptr;
	char	*tmp;
	
	pos = check_redirection(tok);
	if (pos != 0)
	{
		ptr = ft_strndup(tok, pos + 1);
		*i += pos;
		add_to_end(list, ptr);
	}
	tmp = ft_redirection(tok, pos);
	add_to_end(list, tmp);
	*i += ft_strlen(tmp) - 1;
}