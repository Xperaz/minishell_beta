#include "../includes/minishell.h"

t_token	*ft_tokens(char *line)
{
	t_token	*list;
	char	*tok;
	int		i;

	list = NULL;
	i = -1;
	while (line[++i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (line[i] == '"' || line[i] == '\'')
			tokenize_quotes(&list, line, &i);
		else
		{
			tok = ft_normal(line, i);
			if (check_redirection(tok) >= 0)
				redirections(&list, tok, &i);
			else
				redirection1(&list, tok, line, &i);
		}
	}
	free(tok);
	return (list);
}