#include "../includes/minishell.h"

typedef struct dollar
{
	size_t		i;
	size_t		c_d;//count old
	size_t		x;
	const char	*temp;
	char		*buff;
}	t_info;

#define S_1	ft_strlen(new_)
#define S_2	ft_strlen(old)

void fast_strncat(char *dest, const char *src, size_t *size)
{
	if (dest && src && size)
		while ((dest[*size] = *src++))
			*size += 1;
}

void	ft_find_sub(const char *old, const char *new_, t_info *info)
{
	if (strstr(info->temp, old) == info->temp)
        {
            info->x = 0;
            fast_strncat(&info->buff[info->i], new_, &info->x);
            info->i += ft_strlen(new_);
            info->temp += ft_strlen(old);
        }
        else
            info->buff[info->i++] = *info->temp++;
}

void	ft_count_old(const char *old, t_info *info)
{
	if (ft_strstr((const char *)&info->temp[info->i], old) == &info->temp[info->i])
    {
            info->c_d++;
            info->i += ft_strlen(old) - 1;
    }
}

void replaceWord(char **str, const char *old, const char *new_)
{
	t_info	info;

    info.temp = (const char *)(*str);
	info.c_d = 0;
	info.i = -1;
	while (info.temp[++(info.i)] != '\0')
		ft_count_old(old, &info);
    info.buff = ft_calloc((info.i + info.c_d * (S_1 - S_2) + 1), sizeof(char));
    if (!info.buff)
        EXIT_FAILURE;
    info.i = 0;
    while (*info.temp)
		ft_find_sub(old, new_, &info);
    free(*str);
    *str = ft_calloc(info.i + 1, sizeof(char));
    if (!(*str))
        EXIT_FAILURE;
    info.i = 0;
    fast_strncat(*str, (const char *)info.buff, &info.i);
    free(info.buff);
}

void	expand_dollar(t_cmd *node)
{
	int		i;
    char    *sub;
    char    *env;

	while (node) 
	{
		i = 0;
		while (node->cmd[i])
		{
			if (is_dollar(node->cmd[i]) >= 0 && node->cmd[i][0] != '\'')
			{
				sub = dollar_substr(node->cmd[i]);
				env = dollar_substr1(node->cmd[i]);
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