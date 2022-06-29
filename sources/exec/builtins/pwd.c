/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houazzan <houazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:16:02 by houazzan          #+#    #+#             */
/*   Updated: 2022/06/27 14:11:00 by houazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../includes/minishell.h"
int   pwd()
{
    t_env *ptr;

    ptr = g_msh.dup_envp;
    while (ptr != NULL)
    {
        if (ft_strcmp(ptr->key, "PWD=") == 0)
            printf("%s\n", ptr->value);
        ptr = ptr->next;
    }
    return (EXIT_SUCCESS);
}