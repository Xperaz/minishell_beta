
#include "../includes/minishell.h"

void display(t_cmd *node) {

	t_cmd	*tmp;
	int i;

	tmp = node;
	while (tmp)
	{
		i = 0;
		while (tmp->cmd[i])
		{
			printf("{%s} ", tmp->cmd[i]);
			i++;
		}
   		tmp = tmp->next;
		printf("\n");
	}
}
/*                        DOLLAR EXPAND                  */

const char	*ft_strstr(const char *str, const char *to_find)
{
	int	i;
	int	len;

	len = ft_strlen(to_find);
	i = 0;
	if (to_find[i++] == '\0')
		return (str);
	while (*str != '\0')
	{
		if (ft_strncmp(str, to_find, len) == 0)
			return (str);
		str++;
	}
	return (0);
}

void fast_strncat(char *dest, const char *src, size_t *size)
{
	if (dest && src && size)
		while ((dest[*size] = *src++))
			*size += 1;
}

void replaceWord(char **str, const char *old, const char *new_)
{
    size_t		i;
	size_t		count_old;
	size_t		x;
	const char	*temp;
	char		*buff;

    temp = (const char *)(*str);
	count_old = 0;
	i = 0;
	while (temp[i] != '\0')
    {
        if (ft_strstr((const char *)&temp[i], old) == &temp[i])
        {
            count_old++;
            i += ft_strlen(old) - 1;
        }
		i++;
    }
    buff = ft_calloc((i + count_old * (ft_strlen(new_) - ft_strlen(old)) + 1), sizeof(char));
    if (!buff)
        EXIT_FAILURE;
    i = 0;
    while (*temp)
    {
        if (strstr(temp, old) == temp)
        {
            x = 0;
            fast_strncat(&buff[i], new_, &x);
            i += ft_strlen(new_);
            temp += ft_strlen(old);
        }
        else
            buff[i++] = *temp++;
    }
    free(*str);
    *str = ft_calloc(i + 1, sizeof(char));
    if (!(*str))
        EXIT_FAILURE;
    i = 0;
    fast_strncat(*str, (const char *)buff, &i);
    free(buff);
}

int	is_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

int	get_env_end(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '$')
			return (i);
		i++;
	}
	return(i);
}

char	*dollar_substr1(char *str)
{
	char	*sub;
	char	*res;
	int		end;
	sub = strchr(str, '$');
	end = get_env_end(sub);
	res = ft_substr(sub, 1, end - 1);
	return (res);
}

char	*dollar_substr(char *str)
{
	char	*sub;
	char	*res;
	int		end;
	sub = strchr(str, '$');
	end = get_env_end(sub);
	res = ft_substr(sub, 0, end);
	return (res);
}

void	expand_dollar(t_cmd *node)
{
	int		i;

	while (node) 
	{
		i = 0;
		while (node->cmd[i])
		{
			if (is_dollar(node->cmd[i]) >= 0)
			{
				char *sub = dollar_substr(node->cmd[i]);
				char *env = dollar_substr1(node->cmd[i]);
				if (getenv(env))
					replaceWord(&node->cmd[i], sub, getenv(env));
				else if (!getenv(env))
					replaceWord(&node->cmd[i], sub, "");
			}
			i++;
		}
		node = node->next;
	}
	
}

/*                         LEXER.                       */

void	ft_lexer(char *line)
{
	t_token	*list;
	char	*cmd;
	t_cmd	*cmd_list;

	cmd = ft_strtrim(line, " ");
	list = ft_tokens(cmd);
	if (!syntax_validation(list))
	{
		printf("Error occured\n");
		rl_on_new_line();
	}
	flag_list(list);
	cmd_list = creat_cmds(list);
	expand_dollar(cmd_list);
	display(cmd_list);
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