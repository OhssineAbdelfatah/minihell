/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blacksniper <blacksniper@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:34:42 by aohssine          #+#    #+#             */
/*   Updated: 2024/11/09 19:30:24 by blacksniper      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pwd(t_cmd *cmd)
{
	struct exec_cmd	*p;
	char			*curd;

	p = (struct exec_cmd *)cmd;
	curd = NULL;
	curd = getcwd(curd, 0);
	if (!curd)
		return (1);
	printf("%s\n", curd);
	free(curd);
	curd = NULL;
	(void)p;
	return (0);
}

static void	update_oldpwd(t_new_cmd *p)
{
	t_env	*tmp;
	char	*working_dir;

	working_dir = NULL;
	working_dir = getcwd(working_dir, 0);
	tmp = env_exist("OLDPWD", *(p->myenv));
	if (!tmp)
	{
		tmp = creat_new_env(ft_strdup("OLDPWD"), working_dir);
		add_back_env(p->myenv, tmp);
	}
	else
		update_env(tmp, working_dir);
}
static void	update_pwd(t_new_cmd *p)
{
	t_env	*tmp;
	char	*working_dir;

	working_dir = NULL;
	working_dir = getcwd(working_dir, 0);
	tmp = env_exist("PWD", *(p->myenv));
	if (!tmp)
	{
		tmp = creat_new_env(ft_strdup("PWD"), working_dir);
		add_back_env(p->myenv, tmp);
	}
	else
		update_env(tmp, working_dir);
}

int	cd(t_cmd *cmd)
{
	t_new_cmd	*p;
	char		*arg;

	p = (t_cmd_exec *)cmd;
	if (ft_strslen(p->argv) == 1)
	{
		if (!(arg = getEnvValue(*(p->myenv), "HOME")))
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
		chdir(arg);
	}
	else
	{
		if (access(p->argv[1], R_OK) != 0)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(p->argv[1], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (1);
		}
		update_oldpwd(p);
		chdir(p->argv[1]);
		update_pwd(p);
	}
	return (0);
}
