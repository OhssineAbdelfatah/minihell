/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counting_things.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:06:31 by ilaasri           #+#    #+#             */
/*   Updated: 2024/10/30 15:06:33 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	counts_and_or(char *s)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			i = get_next_quote(s, i);
		if (s[i] == '|' && s[i + 1] == '|')
			res++;
		if (s[i] == '&' && s[i + 1] == '&')
			res++;
		i++;
	}
	return (res);
}

int count_red (char *s, t_count_pipe_red *var)
{
	if (s[var->i] == '>')
    {
        if (s[var->i + 1] == '>')
            var->i++;
        var->res++;
    }
    if (s[var->i] == '<')
    {
        if (s[var->i + 1] == '<')
            var->i++;
        var->res++;
    }
    return 0;
}

int	count_pipe_red(char *s)
{
    t_count_pipe_red var;

	var.i = 0;
	var.ref = NOTHING;
	var.res = 0;
	while (s[var.i])
	{
		if (s[var.i] == '\'' || s[var.i] == '"')
			var.i = get_next_quote(s, var.i);
		if (s[var.i + 1] != '|' && s[var.i] == '|')
		{
			var.res++;
			if (var.i > 0 && s[var.i - 1] == '|')
				var.res--;
		}
        if (s[var.i] == '<' || s[var.i] == '>')
            count_red(s, &var);
		// if (s[i] == '>')
		// {
		// 	if (s[i + 1] == '>')
		// 		i++;
		// 	res++;
		// }
		// if (s[i] == '<')
		// {
		// 	if (s[i + 1] == '<')
		// 		i++;
		// 	res++;
		// }
		var.i++;
	}
	return (var.res);
}