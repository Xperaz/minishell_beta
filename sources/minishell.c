/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houazzan <houazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:08:16 by houazzan          #+#    #+#             */
/*   Updated: 2022/05/28 13:20:04 by houazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void display(t_token* node) {

	t_token	*tmp;
	tmp = node;
  while (tmp != NULL) {
    printf("{%s} ", tmp->data);
    tmp = tmp->next;
  }
  printf("\n");
}


/* **************************************************** */
/*                     get_tokens                       */
/* **************************************************** */

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
	while (j < i)
		res[j++] = tok[start++];
	res[j] = '\0';
	return (res);
}

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
	while (i--)
		tok[j++] = line[len++];
	tok[j] = '\0';
	return(tok);
}

char	*ft_double_quote(t_token *list,char *line, int start)
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

t_token	*ft_tokens(char *line)
{
	t_token		*list;
	int			i;
	int			len;
	char		*tok;

	list = NULL;
	i = 0;
	while (line[i])
	{
		while (ft_isspace(line[i]))
				i++;
		if (line[i] == '"')
		{
			add_to_end(&list, ft_double_quote(list, line, i + 1));
			i += ft_strlen(ft_double_quote(list, line, i + 1));
			i++;
		}
		else if (line[i] == '\'')
		{
			add_to_end(&list, ft_single_quote(line, i + 1));
			i += ft_strlen(ft_single_quote(line, i + 1));
		}
		else
		{
			tok = ft_normal(line, i);
			if (check_redirection(tok) >= 0)
			{
				int pos = check_redirection(tok);
				if (pos != 0)
				{
					char *ptr = ft_strndup(tok, pos + 1);
					i += pos;
					add_to_end(&list, ptr);
				}
				char *tmp = ft_redirection(tok, pos);
				add_to_end(&list, tmp);
				i += ft_strlen(tmp) - 1;
			}
			else
			{
				add_to_end(&list, tok);
				i += ft_strlen(ft_normal(line, i + 1));
			}
		}
		i++;
	}
	return (list);
}

void	ft_lexer(char *line)
{
	t_token	*list;
	char	*cmd;

	cmd = ft_strtrim(line, " ");
	list = ft_tokens(cmd);
	display(list);
}

/* **************************************************** */
/*                🆁🅴🅰🅳_🅲🅾🅼🅼🅰🅽🅳                   */
/* **************************************************** */

void	ft_prompt(void)
{
	char	*command;
	while (1)
	{
		command = readline("$> ");
		ft_check(command);
		if (command_checker(command) != 0)
			break ;
		ft_lexer(command);
		free (command);
	}
}

/* **************************************************** */
/*                        🅼🅰🅸🅽                       */
/* **************************************************** */

int	main(void)
{
	ft_prompt();
	return (0);
}