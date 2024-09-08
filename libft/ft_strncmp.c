/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:15:12 by ilaasri           #+#    #+#             */
/*   Updated: 2023/12/09 00:33:20 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	int				res;
	unsigned char	*sf;
	unsigned char	*sl;

	i = 0;
	sf = (unsigned char *)s1;
	sl = (unsigned char *)s2;
	res = 0;
	while ((sf[i] || sl[i]) && i < n)
	{
		if (res == 0)
		{
			res = sf[i] - sl[i];
			if (res > 0)
				return (1);
			if (res < 0)
				return (-1);
		}
		i++;
	}
	return (res);
}
