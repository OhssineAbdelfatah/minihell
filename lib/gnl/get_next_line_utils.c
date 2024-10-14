/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:11:34 by aohssine          #+#    #+#             */
/*   Updated: 2024/02/20 17:16:51 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*join(char *s1, char *s2)
{
	int		j;
	int		k;
	char	*s;

	k = 0;
	if (!s1 || !s2)
		return (NULL);
	s = ft_calloc(ft_strlen(s2) + ft_strlen(s1) + 1, 1);
	if (!s)
		return (NULL);
	while (s1[k])
	{
		s[k] = s1[k];
		k++;
	}
	j = 0;
	while (s2[j])
	{
		s[k] = s2[j];
		j++;
		k++;
	}
	s[k] = 0;
	return (s);
}

int	find_char(char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s && s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*trim_line(char *s)
{
	int		i;
	int		nl;
	char	*line;

	nl = 0;
	if (!s || s[0] == 0)
		return (NULL);
	while (s[nl] && s[nl] != '\n')
		nl++;
	line = ft_calloc(nl + 2, 1);
	if (!line)
		return (NULL);
	i = 0;
	while (s && s[i] && i < (nl + 1))
	{
		line[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
		line[nl + 1] = 0;
	else
		line[nl + 1] = 0;
	return (line);
}

char	*hold_grbg(char *buffer)
{
	int		i;
	int		nl;
	char	*new_buffer;

	nl = 0;
	if (!buffer || buffer[0] == 0)
	{
		free(buffer);
		return (NULL);
	}
	while (buffer[nl] && buffer[nl] != '\n')
		nl++;
	new_buffer = ft_calloc(ft_strlen(buffer) - nl++, 1);
	if (!new_buffer)
	{
		free(buffer);
		return (NULL);
	}
	i = -1;
	while (buffer[nl + ++i])
		new_buffer[i] = buffer[nl + i];
	new_buffer[i] = 0;
	free(buffer);
	return (new_buffer);
}
