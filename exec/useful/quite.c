/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quite.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houazzan <houazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:20:05 by houazzan          #+#    #+#             */
/*   Updated: 2022/06/28 13:09:05 by houazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../includes/minishell.h"

void    free_msh(t_msh *msh)
{
	// if (msh->dup_envp)
	// 	ft_lstclear(&msh->dup_envp, del);
	// if (msh->input_history)
	//     ft_lstdel(&msh->input_history, free_input);
	// if (msh->ast)
	//     ft_lstdel(&msh->ast, free_ast);
	// if (msh->termcaps)
	//     ft_lstdel(&msh->termcaps, free_termcaps);
	// if (msh->curr_cmd_table)
	//     ft_lstdel(&msh->curr_cmd_table, free_cmd_table);
}

void	quit_minishell(int exit_code, char *error_msg)
{
	printf("%s\n", error_msg);
	//free_msh(&g_msh);
	g_msh.exit_status = exit_code;
	exit(exit_code);
}

int    ft_error(char *str, char *err_type, char *command)
{
	printf("%s:", command);
	printf("'%s'", str);
	printf("%s\n", err_type);
	return (0);
}
