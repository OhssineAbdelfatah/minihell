/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:36:16 by aohssine          #+#    #+#             */
/*   Updated: 2024/11/09 22:30:54 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*initialize_tokens(int length)
{
	char	*tokens;
	int		i;

	tokens = ft_calloc(length + 1, sizeof(char));
	i = 0;
	while (i <= length)
	{
		tokens[i] = '0';
		i++;
	}
	return (tokens);
}

void	process_tokens(char *arg, char *tokens, t_tokens tok)
{
	while (arg[tok.i])
	{
		if (arg[tok.i] == '\"' && !tok.in_single_quotes)
		{
			tokens[tok.i] = 'd';
			tok.in_double_quotes = !tok.in_double_quotes;
		}
		else if (arg[tok.i] == '\'' && !tok.in_double_quotes)
		{
			tokens[tok.i] = 's';
			tok.in_single_quotes = !tok.in_single_quotes;
		}
		else if (!tok.in_single_quotes && !tok.in_double_quotes
			&& (tok.prevChar == '\'' || tok.prevChar == '\"' || tok.i == 0))
		{
			tokens[tok.i] = 'w';
		}
		tok.prevChar = arg[tok.i];
		if (tokens[tok.i] == '0')
		{
			if (tok.in_double_quotes)
				tokens[tok.i] = 'd';
			else if (tok.in_single_quotes)
				tokens[tok.i] = 's';
			else
				tokens[tok.i] = 'w';
		}
		tok.i++;
	}
	tokens[tok.i] = '\0';
}

char	*tokenizer(char *arg)
{
	int			len;
	t_tokens	tok;
	char		*tokens;

	len = ft_strlen(arg);
	tok.in_double_quotes = false;
	tok.in_single_quotes = false;
	tok.prevChar = ' ';
	tok.i = 0;
	tokens = initialize_tokens(len);
	process_tokens(arg, tokens, tok);
	return (tokens);
}

t_node	*create_node(char *value, char type)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node->str = value;
	node->type = type;
	node->next = NULL;
	return (node);
}
