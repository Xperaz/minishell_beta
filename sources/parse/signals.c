/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houazzan <houazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 13:56:36 by aouhadou          #+#    #+#             */
/*   Updated: 2022/07/02 14:39:11 by houazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		printf("\033[K$>\n");
		rl_replace_line("", 0);

		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ctrl_d(char *str)
{
	printf("\033[1A\033[3Cexit\n");
	free(str);
	exit(0);
}
