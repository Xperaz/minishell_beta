#include "../includes/minishell.h"

int	ft_isspace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

char	*ft_strndup(char *str, int n)
{
	char	*ret;

	ret = (char *)malloc(n);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, str, n);
	return (ret);
}

char	*ft_normal(char *line, int start)
{
	int		i;
	char	*tok;
	int		len;
	int		j;

	i = 0;
	len = start;
	while (line[start] != ' ' && line[start] != '\0' && line[start] != '\'' && line[start] != '"' && line[start] != '\'')
	{
		start++;
		i++;
	}
	tok = (char *)malloc((i + 1) * sizeof(char));
	j = 0;
	tok[i] = '\0';
	while (j < i)
		tok[j++] = line[len++];
	return(tok);
}

