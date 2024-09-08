/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 12:54:11 by ilaasri           #+#    #+#             */
/*   Updated: 2023/12/08 15:31:13 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (s[0] == '\0' && (char)c == '\0')
	{
		return ((char *)s);
	}
	while (s[i] != 0)
	{
		if (s[i] == (char)c)
		{
			return ((char *)s + i);
		}
		i++;
		if (s[i] == '\0' && (char)c == '\0')
		{
			return ((char *)s + i);
		}
	}
	return (NULL);
}
