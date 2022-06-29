// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   unset.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: houazzan <houazzan@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/06/11 13:14:52 by houazzan          #+#    #+#             */
// /*   Updated: 2022/06/13 10:54:53 by houazzan         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

//#include "../../../includes/minishell.h"


// int      remove_variable(t_list *command_list, t_env *env_list)
// {
// 	t_env *ptr_del;
// 	t_env *ptr;

// 	if (env_list == NULL)
// 		return (0);
// 	ptr = env_list;
// 	while(ptr != NULL)
// 	{
// 		if ((ptr->next) && ft_strcmp(ptr->next->key, command_list->content) == 0)
// 		{
// 			ptr_del = ptr->next;
// 			if (ptr->next->next != NULL)
// 				ptr = ptr->next->next;
// 			else
// 				ptr->next = NULL;
// 			free(ptr_del);
// 		}
// 		ptr = ptr->next;
// 	}
// 	return (1);
// }

// void    unset(t_list *command_list, t_env *env_list)
// {
// 	int i;

// 	i = 0;
// 	command_list = command_list->next;
// 	while (command_list != NULL)
// 	{
// 		while (command_list->content[i])
// 		{
// 			if (!ft_isalnum(command_list->content[i]) && command_list->content[i] != '_')
// 			{
// 				ft_error(command_list->content, INVALID, "unset");
// 				break;
// 			}
// 			i++;
// 		}
// 		remove_variable(command_list, env_list);      
// 		command_list = command_list->next;
// 	}
// }

// ! Frees the data in the pointer and sets the pointer to null
