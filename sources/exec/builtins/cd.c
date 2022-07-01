/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houazzan <houazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:58:56 by houazzan          #+#    #+#             */
/*   Updated: 2022/06/30 16:27:50 by houazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/* **************************************************** */
/*                   🅷🆈🅿🅷🅴🅽_🅴🆇🅿🅰🅽🅳              */
/* **************************************************** */

void	hyphen_expand()
{
	char	*old_pwd;
	t_env	*ptr;
	
	ptr = g_msh.dup_envp;
	
	old_pwd = 0;
	while (ptr != NULL)
	{
		if (ft_strcmp(ptr->key, "OLDPWD=") == 0)
			old_pwd = ptr->value;
		ptr = ptr->next;
	}
	if (ft_strcmp(g_msh.cmd->cmd[1], "-") == 0)
		g_msh.cmd->cmd[1] = ft_strdup (old_pwd);
}

/* **************************************************** */
/*                   🅲🅷🅰🅽🅶🅴_🅴🅽🆅                   */
/* **************************************************** */

void	change_env(char *c_pwd)
{
	char	*pwd;
	t_env	*ptr;

	ptr = g_msh.dup_envp;
	while (ptr != NULL)
	{
		if (ft_strcmp(ptr->key, "PWD=") == 0)
		{
			pwd = ft_strdup(ptr->value);
			ptr->value = ft_strdup(c_pwd);
		}
		ptr = ptr->next;
	}
	ptr = g_msh.dup_envp;
		while (ptr != NULL)
	{
		if (ft_strcmp(ptr->key, "OLDPWD=") == 0)
			ptr->value = ft_strdup(pwd);
		ptr = ptr->next;
	}
}

/* **************************************************** */
/*              🅲🅳_🆆🅸🆃🅷_🅾🅿🅴🆁🅰🅽🅳🆂               */
/* **************************************************** */

void cd_with_operands(char *c_pwd)
{
	int old_pwd;


	old_pwd = 0;
	if (ft_strcmp(g_msh.cmd->cmd[1], "-") == 0)
	{
		hyphen_expand();
			old_pwd = 1;
	}
	if (ft_strcmp(g_msh.cmd->cmd[1], "\0") == 0)
		quit_minishell(1, "cd: OLDPWD not set\n");
	if (chdir(g_msh.cmd->cmd[1]) != 0)
		quit_minishell(errno, strerror(errno));
	else
		if ((c_pwd = getcwd(NULL, 0)) == NULL)
			quit_minishell(errno, strerror(errno));
	change_env(c_pwd);
	if (old_pwd == 1)
		printf("%s\n", c_pwd);
}
/* **************************************************** */
/*              🅲🅳_🅽🅾_🅾🅿🅴🆁🅰🅽🅳🆂                  */
/* **************************************************** */

void cd_no_operands(char *c_pwd)
{
	if (chdir(getenv("HOME")) != 0)
		quit_minishell(errno, strerror(errno));
	else
		if ((c_pwd = getcwd(NULL, 0)) == NULL)
			quit_minishell(errno, strerror(errno));
	change_env(c_pwd);
}

/* **************************************************** */
/*                          🅲🅳                         */
/* **************************************************** */

int 	cd()
{
	char	*c_pwd;
    int     i;

    i = 1;

	c_pwd = malloc(sizeof(char) * 1024);
    if (!c_pwd)
        quit_minishell(errno, strerror(errno));
	if (g_msh.cmd->cmd[i] != NULL)
        cd_with_operands(c_pwd);
	else 
		cd_no_operands(c_pwd);
	return(0);
}
