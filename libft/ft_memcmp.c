/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 21:56:59 by ilaasri           #+#    #+#             */
/*   Updated: 2023/12/22 15:38:22 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*sf;
	unsigned char	*sl;
	unsigned int	i;

	i = 0;
	sf = (unsigned char *)s1;
	sl = (unsigned char *)s2;
	while (i < n)
	{
		if ((sf[i] - sl[i]) != 0)
			return (sf[i] - sl[i]);
		i++;
	}
	return (0);
}
