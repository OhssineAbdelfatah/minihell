/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:35:23 by aohssine          #+#    #+#             */
/*   Updated: 2024/11/09 21:23:41 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_error(t_cmd_exec *p, char **abs_path)
{
	struct stat file;

	if (p->argv[0] && (p->argv[0][0] == '/' || (p->argv[0][0] == '.'
				&& p->argv[0][1] == '/') || (p->argv[0][0] == '.'
				&& p->argv[0][1] == '.' && p->argv[0][2] == '/')))
	{
		if (stat(p->argv[0], &file) == -1)
		{
			write(2, "minishell: no such file or directory\n", 38);
			exit(127);
		}
		else if (S_ISDIR(file.st_mode))
		{
			write(2, "minishell: ", 11);
			write(2, p->argv[0], ft_strlen(p->argv[0]));
			write(2, "is a directory\n", 16);
			exit(126);
		}
		else if (S_ISREG(file.st_mode) && !(file.st_mode & S_IXUSR))
		{
			write(2, "minishell: permission denied\n", 30);
			exit(126);
		}
		else if (S_ISREG(file.st_mode) && file.st_mode & S_IXUSR)
		{
			*abs_path = p->argv[0];
			return ;
		}
	}
	else
	{
		*abs_path = get_env_value(*(p->myenv), "PATH");
		if (!(*abs_path))
			error_exec_new(p->argv[0], 1);
		*abs_path = cmd_abs_path(*abs_path, p->argv[0]);
		if (!abs_path)
			error_exec_new(p->argv[0], 127);
	}
}
