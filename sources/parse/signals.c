/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 13:56:36 by aouhadou          #+#    #+#             */
/*   Updated: 2022/07/03 21:35:04 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_sig(int sig)
{
	int	i;

	i = 0;
	if (sig == SIGINT && g_msh.signal == 0)
	{
		rl_replace_line("", 0);
		printf("\033[K$>\n");
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGINT && g_msh.signal == 5)
		i++;
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
