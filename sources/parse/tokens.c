/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:08:24 by ilaasri           #+#    #+#             */
/*   Updated: 2024/10/30 15:08:26 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	red_or_pipe(char c)
{
	if (0 == c)
		return (-1);
	if (c == '|')
		return (PIPE);
	if (c == '>' || c == '<')
		return (RED);
	return (-2);
}

int	get_starto(char *s, int x)
{
	if (s[x] == 0)
		return (x);
	if (0 == is_white(s[x]))
		return (skip_spaces(s, x));
	if (0 == x)
		return (x);
	return (x);
}

int red_or_pipe_check(char *s, t_ct_tk_pro *var)
{
	if (s[var->i] == '|')
	{
		if (s[var->i + 1] == '|')
			var->ref = AND;
		if (var->ref == NOTHING || var->ref == PIPE || var->ref == RED)
			return (-1);
		var->ref = PIPE;
		var->res++;
		var->i++;
	}
	if (RED == red_or_pipe(s[var->i]))
	{
		if (RED == var->ref)
			return (-2);
		var->ref = RED;
		var->res++;
		while (s[var->i] && (RED == red_or_pipe(s[var->i])))
			var->i++;
	}
	return 0;
}

int las_part_pro(char *s, t_ct_tk_pro *var)
{
	if (s[var->i] && is_white(s[var->i]) && (0 == is_special(s[var->i])) && s[var->i] != '\''
			&& s[var->i] != '"')
		{
			if (var->ref == RED)
				var->ref = FILE_NAME;
			else
				var->ref = EXEC;
			var->res++;
			while (s[var->i] && is_white(s[var->i]) && (0 == is_special(s[var->i]))
				&& s[var->i] != '\'' && s[var->i] != '"')
			{
				var->i++;
				if (s[var->i] == '\'' || s[var->i] == '"')
				{
					while (s[var->i] && (s[var->i] == '\'' || s[var->i] == '"'))
						var->i = get_next_quote(s, var->i) + 1;
				}
			}
		}
		if (0 == s[var->i] && RED == var->ref)
			return (-2);
		if (0 == s[var->i] && PIPE == var->ref)
			return (-1);
	return (0);

}

void middle_game(char *s, t_ct_tk_pro *var)
{
	if (s[var->i] == '\'' || s[var->i] == '"')
	{
		var->ref = STRING;
		var->res++;
		while (s[var->i] && (s[var->i] == '\'' || s[var->i] == '"'))
		{
			var->i = get_next_quote(s, var->i) + 1;
			while (s[var->i] && is_white(s[var->i]) && (0 == is_special(s[var->i]))
				&& s[var->i] != '\'' && s[var->i] != '"')
				var->i++;
		}
	}
}

int	count_tokens_pro(char *s)
{
	t_ct_tk_pro var;

	if (NULL == s)
		return (0);
	var.res = 0;
	var.i = 0;
	var.ref = NOTHING;
	while (s[var.i])
	{
		var.i = skip_spaces(s, var.i);
		var.tmp = red_or_pipe_check(s,&var);
		if (var.tmp < 0)
			return (var.ref);
		var.i = skip_spaces(s, var.i);
		middle_game(s, &var);
		var.i = skip_spaces(s, var.i);
		var.tmp = las_part_pro(s, &var);
		if (0 != var.tmp)
			return (var.tmp);
	}
	return (var.res);
}
// int	count_tokens_pro(char *s)
// {
// 	// t_ct_tk_pro var;
// 	int	res;
// 	int	i;
// 	int	ref;

// 	if (NULL == s)
// 		return (0);
// 	res = 0;
// 	i = 0;
// 	ref = NOTHING;
// 	while (s[i])
// 	{
// 		i = skip_spaces(s, i);
// 		ref = red_or_pipe_check(s,&var);
// 		if (ref < 0)
// 			return (ref);
// 		// if (s[i] == '|')
// 		// {
// 		// 	if (s[i + 1] == '|')
// 		// 		ref = AND;
// 		// 	if (ref == NOTHING || ref == PIPE || ref == RED)
// 		// 		return (-1);
// 		// 	ref = PIPE;
// 		// 	res++;
// 		// 	i++;
// 		// }
// 		// if (RED == red_or_pipe(s[i]))
// 		// {
// 		// 	if (RED == ref)
// 		// 		return (-2);
// 		// 	ref = RED;
// 		// 	res++;
// 		// 	while (s[i] && (RED == red_or_pipe(s[i])))
// 		// 		i++;
// 		// }
// 		i = skip_spaces(s, i);
// 		if (s[i] == '\'' || s[i] == '"')
// 		{
// 			ref = STRING;
// 			res++;
// 			while (s[i] && (s[i] == '\'' || s[i] == '"'))
// 			{
// 				i = get_next_quote(s, i) + 1;
// 				while (s[i] && is_white(s[i]) && (0 == is_special(s[i]))
// 					&& s[i] != '\'' && s[i] != '"')
// 					i++;
// 			}
// 		}
// 		i = skip_spaces(s, i);
// 		if (s[i] && is_white(s[i]) && (0 == is_special(s[i])) && s[i] != '\''
// 			&& s[i] != '"')
// 		{
// 			if (ref == RED)
// 				ref = FILE_NAME;
// 			else
// 				ref = EXEC;
// 			res++;
// 			while (s[i] && is_white(s[i]) && (0 == is_special(s[i]))
// 				&& s[i] != '\'' && s[i] != '"')
// 			{
// 				i++;
// 				if (s[i] == '\'' || s[i] == '"')
// 				{
// 					while (s[i] && (s[i] == '\'' || s[i] == '"'))
// 						i = get_next_quote(s, i) + 1;
// 				}
// 			}
// 		}
// 		if (0 == s[i] && RED == ref)
// 			return (-2);
// 		if (0 == s[i] && PIPE == ref)
// 			return (-1);
// 	}
// 	return (res);
// }

int	count_words(char *s)
{
	int	i;
	int	res;
	int	ref;

	i = 0;
	res = 0;
	if (!s)
		return (0);
	ref = NOTHING;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			i = get_next_quote(s, i);
			if (ref != STRING)
				res++;
			ref = STRING;
		}
		if (0 == is_white(s[i]))
			ref = SPACES;
		if (0 <= is_special(s[i]))
			ref = SPECIAL;
		if ((s[i] != '"' || s[i] != '\'') && (is_white(s[i]) &&
				-1 == is_special(s[i])))
		{
			if (ref != STRING)
			{
				ref = STRING;
				res++;
			}
		}
		i++;
	}
	return (res);
}

int	get_next_parenties_d(char **s, int i)
{
	int	ref;

	ref = 0;
	while (s[i])
	{
		if (which_one(s[i]) == END_SUB && ref == 0)
			return (i);
		else if (which_one(s[i]) == END_SUB && ref != 0)
			ref--;
		i++;
		if (which_one(s[i]) == S_SUB)
			ref++;
	}
	error(NULL, 40);
	return (-1);
}

int	get_tok_len(char *s)
{
	int	pipe_red;
	int	and_or;
	int	words;
	int	sub_sh;
	int	res;

	if (!s)
		return (0);
	and_or = counts_and_or(s);
	pipe_red = count_pipe_red(s);
	words = count_words(s);
	sub_sh = count_sub_sh(s);
	if (sub_sh < 0)
		return (-1);
	res = words + and_or + pipe_red + sub_sh;
	return (res);
}

int	get_endo(char *s, int x)
{
	int	j;

	if (s[x] == 0)
		return (x);
	if (0 <= is_special(s[x]))
	{
		if (s[x] == 40 || s[x] == 41)
			return (x + 1);
		j = is_special(s[x]);
		while (s[x] && j == is_special(s[x]))
			x++;
		return (x);
	}
	if (-1 == is_special(s[x]) && is_white(s[x]))
	{
		if (s[x] == '\'' || s[x] == '"')
		{
			while (-1 == is_special(s[x]) && is_white(s[x]) && (s[x] == '\''
					|| s[x] == '"'))
				x = get_next_quote(s, x) + 1;
		}
		while (s[x] && (-1 == is_special(s[x])) && is_white(s[x]))
		{
			if (s[x] == '\'' || s[x] == '"')
			{
				while (s[x] && (s[x] == '\'' || s[x] == '"'))
					x = get_next_quote(s, x) + 1;
			}
			else
				x++;
		}
	}
	return (x);
}

char	**fr9_trb7(char *s)
{
	t_tfar9	var;

	if (NULL == s)
		return (NULL);
	var.reslen = get_tok_len(s);
	if (var.reslen <= 0)
		return (NULL);
	var.res = (char **)malloc(sizeof(char *) * (var.reslen + 1));
	if (NULL == var.res)
		return (NULL);
	var.i = 0;
	var.end = 0;
	while (var.i < var.reslen)
	{
		var.start = get_starto(s, var.end);
		var.end = get_endo(s, var.start);
		var.res[var.i] = ft_substr(s, var.start, var.end - var.start);
		if (NULL == (var.res[var.i]))
			panic("malloc failed !\n");
		var.i++;
	}
	var.res[var.i] = NULL;
	return (var.res);
}

int check_ref(int i, char **tokens)
{
	int ref;
	int next_ref;

	ref = which_one(tokens[i]);
	next_ref = which_one(tokens[i + 1]);
	if (ref != EXEC && ref == next_ref)
	{
		if (ref != S_SUB && ref != END_SUB)
			return (ref);
	}
	if (ref == RED || ref == HERDOC)
	{
		if (next_ref != EXEC)
			return (ref);
	}
	if (ref == PIPE || ref == AND || ref == OR)
	{
		if (next_ref != EXEC && next_ref != RED && next_ref != HERDOC)
		{
			if (next_ref != S_SUB && next_ref != END_SUB)
				return (ref);
		}
	}
	return (-1);
}

int	_check_tokens(char **tokens)
{
	int	i;
	int ref;
	int next_ref;

	i = 0;
	ref = EXEC;
	if (!tokens)
		return (0);
	ref = which_one(tokens[i]);
	if (ref == AND || ref == PIPE || ref == OR)
		return (ref);
	if (check_tok_sub(tokens))
		return (1008);
	while (tokens[i])
	{
		ref = which_one(tokens[i]);
		i++;
		next_ref = which_one(tokens[i]);
		if (ref != EXEC && ref == next_ref)
		{
			if (ref != S_SUB && ref != END_SUB)
				return (ref);
		}
		if (ref == RED || ref == HERDOC)
		{
			if (next_ref != EXEC)
				return (ref);
		}
		if (ref == PIPE || ref == AND || ref == OR)
		{
			if (next_ref != EXEC && next_ref != RED && next_ref != HERDOC)
			{
				if (next_ref != S_SUB && next_ref != END_SUB)
					return (ref);
			}
		}
	}
	if (ref == END_SUB)
		ref = SUB_SH;
	return (ref);
}
