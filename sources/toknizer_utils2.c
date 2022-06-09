#include "../includes/minishell.h"

char	*ft_single_quote(char *line, int start)
{
	int		i;
	char	*tok;
	int		len;
	int		j;

	i = 0;
	len = start;
	while (line[start] != '\'' && line[start] != '\n' && line[start] != '\0')
	{
		start++;
		i++;
	}
	tok = (char *)malloc((i + 1) * sizeof(char));
	j = 0;
	tok[i] = '\0';
	while ( j < i)
		tok[j++] = line[len++];
	return(tok);
}

char	*ft_double_quote(char *line, int start)
{
	int		i;
	char	*tok;
	int		len;
	int		j;

	i = 0;
	len = start;
	while (line[start] != '"' && line[start] != '\0')
	{
		start++;
		i++;
	}
	tok = (char *)malloc((i + 1) * sizeof(char));
	j = 0;
	while (j < i)
		tok[j++] = line[len++];
	tok[j] = '\0';
	return(tok);
}

void	single_quotes(t_token **list, char *line, int *i)
{
	add_to_end(list, ft_single_quote(line, *i + 1));
	*i += ft_strlen(ft_single_quote(line, *i + 1)) + 1;
}

void	double_quotes(t_token **list, char *line, int *i)
{
	char *ptr;

	ptr = ft_double_quote(line, *i + 1);
	add_to_end(list, ptr);
	*i += ft_strlen(ptr) + 1;
}

void	tokenize_quotes(t_token **list, char *line, int *i)
{
	if (line[*i] == '"')
		double_quotes(list, line, i);
	else if (line[*i] == '\'')
		single_quotes(list, line, i);
}