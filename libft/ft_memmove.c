/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 21:14:28 by ilaasri           #+#    #+#             */
/*   Updated: 2023/12/10 22:50:23 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	// size_t	i;
	char	*s;
	char	*d;

	// i = 0;
	s = (char *)src;
	d = (char *)dst;
	if (!s && !d)
		return (NULL);
	if ((size_t)(d - s) < len)
	{
		while (len-- > 0)
		{
			d[len] = s[len];
		}
	}
	else
	{
		ft_memcpy(dst, src, len);
	}
	return (dst);
}
