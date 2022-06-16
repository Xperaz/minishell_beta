#include "../includes/minishell.h"

int	wich_redirection(char *red)
{
	int	flag;

	flag = 0;
	if ( !strncmp(red, ">>", 2))
		flag = ASO;
	else if ( !strncmp(red, "<<", 2))
		flag = ASI;
	else if ( !strncmp(red, ">", 1))
		flag = O_REDIRECTION;
	else if ( !strncmp(red, "<", 1))
		flag = I_REDIRECTION;
	return (flag);

}

int		check_cmd(char *tok)
{
	int		flag;

	flag = 0;
	if (tok[0] == '-')
		flag = OPTION;
	else if (!ft_strncmp(tok, "$", 1))
		flag = DOLLAR;
	else
		flag = COMMAND;
	return (flag);
}

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
	int		flag;
	ptr = ft_normal(line, *i + 1);
	flag = check_cmd(tok);
	add_to_end(list, tok, flag);
	//printf("[%s]\n", ptr);
	*i += ft_strlen(ptr);
}

void	redirections(t_token **list, char *tok, int *i)
{
	int		pos;
	char	*ptr;
	char	*tmp;
	int		flag;
	
	pos = check_redirection(tok);
	if (pos != 0)
	{
		ptr = ft_strndup(tok, pos + 1);
		*i += pos;
		add_to_end(list, ptr, OPTION);
	}
	tmp = ft_redirection(tok, pos);
	flag = wich_redirection(tmp);
	add_to_end(list, tmp, flag);
	*i += ft_strlen(tmp) - 1;
}