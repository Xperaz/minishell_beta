/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houazzan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 18:40:25 by houazzan          #+#    #+#             */
/*   Updated: 2021/11/15 18:43:21 by houazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ptr;
	t_list	*de;

	ptr = *lst;
	if (*lst == NULL)
		return ;
	while (ptr != NULL)
	{
		de = ptr->next;
		del(ptr->content);
		free(ptr);
		ptr = de;
	}
	*lst = NULL;
}
