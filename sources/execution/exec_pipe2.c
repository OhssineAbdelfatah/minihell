/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 22:49:46 by ilaasri           #+#    #+#             */
/*   Updated: 2024/11/09 22:49:47 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	left_child_is_sub(t_cmd *left_cmd, t_execp *sp, int *last_status)
{
	t_sub_sh *left_sub;

	left_sub = (t_sub_sh *)left_cmd;
	if (sp->node_p->pipe_fd != -1)
		left_sub->fd_in = sp->node_p->pipe_fd;
	left_sub->fd_out = sp->p[1];
	close(sp->p[0]);
	*last_status = exec_sub_sh(left_cmd, last_status);
	if (left_sub->herdoc->herdoc_pipe > 0)
		close(left_sub->herdoc->herdoc_pipe);
	exit(*last_status);
}