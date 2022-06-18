#include "../includes/minishell.h"

void	remove_all_chars(char* str, char c)
{
	char	*pr;
	char	*pw;

	pr = str;
	pw = str;
    while (*pr)
	{
        *pw = *pr++;
        pw += (*pw != c);
    }
    *pw = '\0';
}

char	*ft_strncpy(char *dst, const char *src, int len)
{
	int	i;

	i = 0;
	while (src[i] && i < len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_sub_str(const char *src, int len)
{
	char	*substr;

	if (!src)
		return (NULL);
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	return (ft_strncpy(substr, src, len));
}

