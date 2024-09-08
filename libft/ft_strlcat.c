/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 23:19:35 by ilaasri           #+#    #+#             */
/*   Updated: 2023/12/24 20:09:04 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	res;
	size_t	i;
	size_t	j;
	size_t	f;

	res = 0;
	i = 0;
	while (dst[i] && res < dstsize)
	{
		i++;
		res++;
	}
	f = ft_strlen(src);
	i = res;
	j = 0;
	if (dstsize && i < (dstsize - 1))
	{
		while (i < (dstsize - 1) && src[j])
		{
			dst[i++] = src[j++];
		}
		dst[i] = '\0';
	}
	return (res + f);
}
