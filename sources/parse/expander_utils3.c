
#include "../../includes/minishell.h"

char	*get_id(int p)
{
	char	*val;
	
	if (p % 2 == 0)
	{
		if (p == 2)
			val = ft_strdup(ft_itoa(getpid()));
		else
			val = ft_strjoin(ft_itoa(getpid()), val);
	}
	return (val);
}

void	replace_id(char *ptr, t_dinfo info)
{
	info.val1[info.j] = '\0';
	if (info.j % 2 != 0)
		info.val1[info.j - 1] = 0;
	replace_sub(&ptr, info.val1, info.val);
}

int	all_vars(char *ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		if (ptr[i] != '$')
			return (0);
		i++;
	}
	return (1);
}

void	call_expander(t_dinfo *info, char *com)
{
	while (info->sub[++info->j] == '$')
	{
		info->val = get_id(info->p);
		info->val1[info->j] = info->sub[info->j];
		info->p++;
	}
	if (info->j % 2 == 0 || info->p > 2)
	{
		replace_id(com, *info);
		free(info->val1);
		free(info->val);
	}
}

void	info_init(t_dinfo *info, char *cmd)
{
	info->sub = dollar_substr(cmd);
	info->flag = 1;
	info->j = -1;
	info->p = 1;
	info->val = NULL;
	info->val1 = malloc(sizeof(char) * ft_strlen(info->sub));
}