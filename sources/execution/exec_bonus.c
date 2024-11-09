/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:35:12 by aohssine          #+#    #+#             */
/*   Updated: 2024/11/09 17:35:13 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int exec_sub_sh(t_cmd * cmd , int *last_status)
{
    t_sub_sh * p;
    int pid;
    int *std[4];
    int sub_status;

    p = (t_sub_sh  *)cmd;
    pid = fork();
    sub_status = 0;
    if (pid == 0)
    {
        signal(SIGQUIT, NULL);
        std[0] = &(p->fd_in);
        std[1] = &(p->fd_out);
        std[2] = &sub_status;
        std[3] = last_status;
        if (p->redirect){
            if (exec_red(p->redirect, std,p->herdoc,*(p->myenv)) == 1)
                exit(1);
        }
        if (p->fd_in != -1 || p->fd_out != -1)
        {
            if (p->fd_out != -1)
            {
                dup2(p->fd_out, 1);
                close(p->fd_out);
            }
            if(p->fd_in != -1)
            {
                dup2(p->fd_in, 0);
                close(p->fd_in);
            }
        }
        sub_status = new_exec(p->sub_root, 0, last_status);
        exit(sub_status);
    }
    signal(SIGQUIT, do_nothing);
    signal(SIGINT, SIG_IGN);
    waitpid(pid, &sub_status, 0);
    *last_status = WEXITSTATUS(sub_status);
    return (*last_status);
}
