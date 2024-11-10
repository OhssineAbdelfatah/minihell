/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:37:40 by aohssine          #+#    #+#             */
/*   Updated: 2024/11/09 17:37:41 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		g_sig;

void	panic(char *str)
{
	if (str)
		ft_putstr_fd(str, 2);
	exit(1);
}

void	parse_nd_exec(char **my_tokens, t_env **dup_env, int *status)
{
	t_cmd	*res;

	res = NULL;
	res = root(my_tokens, dup_env);
	if (!res)
		return ;
	if (g_sig == -1)
		*status = new_exec(res, NOTHING, status);
	if (g_sig == 130 || g_sig == 131)
	{
		*status = 130;
        if (g_sig == 131)
            *status = 1;
		g_sig = -1;
	}
	free_mynigga(my_tokens);
	free_tree2(res);
}

void	history(char *str)
{
	if (!str)
    {
        ft_putstr_fd("exit\n", 2);
        exit(0);
    }
	if (!str || 0 == ft_strlen(str))
		return ;
	if (is_white_str(str))
		return ;
	add_history(str);
}


void ff(){
    system("leaks minishell");
}

int main(int ac, char **av, char **env)
{
    char *str;
    int status;
    char **my_tokens;
    t_env *dup_env;
    int checker ;   

    status = 0;
    dup_env = init_env(env);
    while(1)
    {
        signal(SIGINT, signal_handler);
        signal(SIGQUIT, SIG_IGN);
        str = readline(GRN"minishell> "CRESET);
        history(str);
        if (g_sig == 1300)
        {
            // printf("Status : %d\n", status);
            status = 1;
        }
        g_sig = -1;
        if (str && ft_strlen(str) && _check_str(str) == 0)
        {
            my_tokens = fr9_trb7(str);
            checker = _check_tokens(my_tokens);
            if (checker != EXEC && checker != SUB_SH)
            {
                free_mynigga(my_tokens);
                error(NULL,checker);
                status = 258;
            }
            else if (my_tokens)
                parse_nd_exec(my_tokens, &dup_env, &status);
        }
        free(str);
    }
    (void)ac;
    (void)av;
}
