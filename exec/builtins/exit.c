// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   exit.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: houazzan <houazzan@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/06/13 11:21:49 by houazzan          #+#    #+#             */
// /*   Updated: 2022/06/15 15:16:54 by houazzan         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */



//#include "../../../includes/minishell.h"

// void    status(int status)
// {
//     t_exit exit;
//     status = (char)status;
// }



// int exit_command(t_list *command_list, t_env *env_list)
// {
//     if (command_list->next == NULL)
//     {
//         status(0);
//         exit(0);
//     }
//     else
//     {
//         status(ft_atoi(command_list->next->content));
//         exit(ft_atoi(command_list->next->content));
//     }
//     return (0);
// }

// ~ if exit is the only command exit we do execute it else we just egnore it ~ //

// ~ if options of exit are non degits we reture an error(if it's the only command we quite minishell and if not we run the next command ~ //)


// ! exit doesn't have to exit if there are more than one simple command 
// ! in cmd_table but it still has to do thorough error handling
// ! Case: no arguments so the exit status sent is the one of the last
// ! executed simple command (e.g. cd asjoafsj; exit; echo $? STDOUT: 1)
// ! Case: first arg is a number but there are more than one arg. Doesn't
// ! exit. Sends error message and returns EXIT_FAILURE
// ! Case: non-numeric argument. Exits with error message
// ! Case: arg is a number and only one arg. Exits with arg as exit code 