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