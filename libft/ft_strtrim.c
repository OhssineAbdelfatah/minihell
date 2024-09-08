/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 16:51:14 by ilaasri           #+#    #+#             */
/*   Updated: 2023/12/24 20:15:27 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	checkif(const char *s, int c)
{
	int	j;

	j = 0;
	while (s[j])
	{
		if (s[j] == c)
			return (1);
		j++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, const char *set)
{
	char	*res;
	size_t	i;
	size_t	lens1;

	if (s1 == NULL || set == NULL)
		return (NULL);
	// if (s1 == '\0' || set == '\0')
	// 	return (ft_strdup(s1));
	i = 0;
	lens1 = ft_strlen(s1);
	while (checkif(set, s1[i]) == 1)
		i++;
	if (i == lens1)
	{
		res = ft_substr(s1, i, 0);
		return (res);
	}
	while (checkif(set, s1[lens1 - 1]) == 1)
		lens1--;
	res = ft_substr(s1, i, (lens1 - i));
	return (res);
}
