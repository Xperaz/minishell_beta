/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houazzan <houazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:02:23 by houazzan          #+#    #+#             */
/*   Updated: 2022/06/27 18:01:28 by houazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../includes/minishell.h"


void    run_builtins()
{

    if (g_msh.cmd->cmd_type == CD)
       g_msh.exit_status = cd();
    else if (g_msh.cmd->cmd_type == ECHO)
      g_msh.exit_status = echo();
    else if (g_msh.cmd->cmd_type == PWD)
        g_msh.exit_status = pwd();
    else if (g_msh.cmd->cmd_type == ENV)
        g_msh.exit_status = env(0);
    else if (g_msh.cmd->cmd_type == EXPORT)
       g_msh.exit_status = export();
    // else if (g_msh.cmd->cmd_type == UNSET)
    //     unset();
//     else if (g_msh.cmd->cmd_type == EXIT)
//         exit();
 }