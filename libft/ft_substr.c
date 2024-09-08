/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 19:44:00 by ilaasri           #+#    #+#             */
/*   Updated: 2023/12/24 05:56:37 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*res;
	size_t			i;
	size_t			sublen;
	size_t			srclen;

	if (!s)
		return (NULL);
	i = 0;
	srclen = ft_strlen(s);
	sublen = len;
	if (start >= srclen)
		return (ft_strdup(""));
	if (srclen <= start + len)
		sublen = srclen - start;
	res = (char *)malloc((sublen + 1) * (sizeof(char)));
	if (!res)
		return (NULL);
	while (i < sublen)
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
