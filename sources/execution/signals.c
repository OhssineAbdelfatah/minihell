/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:43:31 by ilaasri           #+#    #+#             */
/*   Updated: 2024/11/09 11:59:29 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void do_nothing(int signal)
{
    (void)signal;
	// printf("SIGNAL :%d\n", signal);
    printf("\n");
    return;
}

void	signal_handler(int signal)
{
	(void)signal;
	printf("\n");
	rl_on_new_line();
	// rl_replace_line("", 0);
	rl_redisplay();
	g_sig =1300;
}
