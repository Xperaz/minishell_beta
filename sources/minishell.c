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


char	*ft_single_quote(char *line, int start)
{
	int		i;
	char	*tok;
	int		len;
	int		j;

	i = 0;
	len = start;
	while (line[start] != '\'' && line[start] != '\0' && line[start] != '\n')
	{
		start++;
		i++;
	}
	tok = (char *)malloc((i + 1) * sizeof(char));
	j = 0;
	tok[i + 1] = '\0';
	while (i--)
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
	tok[i + 1] = '\0';
	while (i--)
		tok[j++] = line[len++];
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
	while (line[start] != ' ' && line[start] != '\0' && line[start] != '\'' && line[start] != '"')
	{
		start++;
		i++;
	}
	tok = (char *)malloc((i + 1) * sizeof(char));
	j = 0;
	tok[i + 1] = '\0';
	while (i--)
		tok[j++] = line[len++];
	return(tok);
}

void	ft_lexer(char *line)
{
	t_token		*list;
	int			i;
	int			len;
	char		*str;

	//cmd = ft_strtrim(line, " ");
	list = NULL;
	i = 0;
	while (line[i])
	{
		while (line[i] == ' ')
				i++;
		if (line[i] != '\'' && line[i] != '"')
		{
			while (line[i] == ' ')
				i++;
			add_to_end(&list, ft_normal(line, i));
			i += ft_strlen(ft_normal(line, i));
		}
		else if (line[i] == '"')
		{
			add_to_end(&list, ft_double_quote(line, i + 1));
			i += ft_strlen(ft_double_quote(line, i + 1));
			i++;
		}
		else if (line[i] == '\'')
		{
			add_to_end(&list, ft_single_quote(line, i + 1));
			i += ft_strlen(ft_single_quote(line, i + 1));
			i++;
		}
		i++;
	}
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