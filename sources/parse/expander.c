/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 13:56:01 by aouhadou          #+#    #+#             */
/*   Updated: 2022/07/02 22:32:47 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

typedef struct dollar_ibfo
{
	int		i;
	char	*sub;
	int		flag;
	char	**ptr;
}	t_dinfo;

void	fast_strncat(char *dest, const char *src, size_t *size)
{
	size_t	src_len;

	if (dest && src)
	{
		src_len = ft_strlen(src);
		ft_memcpy(dest + *size, src, src_len + 1u);
		*size += src_len;
	}
}

void	ft_find_sub(const char *old, const char *new_, t_info *info)
{
	if (ft_strstr(info->temp, old) == info->temp)
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
	const char	*str;

	str = ft_strstr((const char *)&info->temp[info->i], old);
	if (str == &info->temp[info->i])
	{
		info->c_d++;
		info->i += ft_strlen(old) - 1;
	}
}

void	replace_sub(char **str, const char *old, const char *new_)
{
	t_info	info;

	info.temp = (const char *)(*str);
	info.c_d = 0;
	info.i = -1;
	info.t = ft_strlen(new_) - ft_strlen(old);
	while (info.temp[++(info.i)] != '\0')
		ft_count_old(old, &info);
	info.buff = ft_calloc((info.i + info.c_d * info.t + 1), sizeof(char));
	if (!info.buff)
		return ;
	info.i = 0;
	while (*info.temp)
		ft_find_sub(old, new_, &info);
	free(*str);
	*str = ft_calloc(info.i + 1, sizeof(char));
	if (!(*str))
		return ;
	info.i = 0;
	fast_strncat(*str, (const char *)info.buff, &info.i);
	free(info.buff);
}

void	expand_dollar(t_command *lst)
{
	t_dinfo	info;

	while (lst)
	{
		info.flag = 0;
		info.i = -1;
		while (lst->cmd[++info.i])
		{
			if (is_dollar(lst->cmd[info.i]) >= 0 && lst->cmd[info.i][0] != '\'')
			{
				info.flag = 1;
				info.sub = dollar_substr(lst->cmd[info.i]);
				int j = 0;
				char *val = malloc(ft_strlen(info.sub) * sizeof(char));
				printf("%s\n", info.sub);
				while (info.sub[j] == '$' && info.sub[j + 1] == '$')
				{
					val[j] = info.sub[j];
					j++;
				}
				printf("{%s} [%d]\n", val, j);
				val[j] = '\0';
				if (j > 0)
				{
					
					replace_sub(&lst->cmd[info.i], val, "123456");
				}
				if (!ft_strcmp1(info.sub, "$"))
				{
					replace_sub(&lst->cmd[info.i], info.sub, "$");
					return ;
				}
				printf("***%s****\n", info.sub);
				info.ptr = ft_split(info.sub, '$');
				fill_tab(info.ptr, &lst->cmd[info.i]);
			}
		}
		if (info.flag == 1)
			ex_free(info.sub, info.ptr);
		lst = lst->next;
	}
}
