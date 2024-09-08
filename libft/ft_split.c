/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 22:08:26 by ilaasri           #+#    #+#             */
/*   Updated: 2023/12/24 06:51:19 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbrst(char const *s, int c)
{
	int	nbr;
	int	i;
	// int	x;

	i = 0;
	// x = 0;
	nbr = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == 0))
			nbr++;
		i++;
	}
	return (nbr);
}

static int	start(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != c)
			return (i);
		i++;
	}
	return (0);
}

static int	end(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (i);
}

static char	**freesplit(char **res, int i)
{
	while (i >= 0)
		free(res[i--]);
	free(res);
	return (NULL);
}

char	**ft_split(char const *s, int c)
{
	int		i;
	int		first;
	int		last;
	char	**res;

	i = -1;
	last = 0;
	if (!s)
		return (NULL);
	res = (char **)malloc((nbrst(s, c) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (++i < nbrst(s, c))
	{
		first = start(s + last, c) + last;
		last = end(s + first, c) + first;
		res[i] = ft_substr(s, first, last - first);
		if (!res[i])
			return (freesplit(res, i));
	}
	res[i] = 0;
	return (res);
}
