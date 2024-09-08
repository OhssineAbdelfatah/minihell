/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 21:40:45 by ilaasri           #+#    #+#             */
/*   Updated: 2023/12/12 23:40:07 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbr(int c)
{
	int			res;
	long int	x;

	x = c;
	res = 1;
	if (x < 0)
	{
		x *= -1;
		res++;
	}
	while (x >= 10)
	{
		x = x / 10;
		res++;
	}
	return (res);
}

static char	*cisneg(int c, char *res, int j, char *base)
{
	long int	x;
	int			i;

	x = c;
	i = j - 1;
	x *= -1;
	res[0] = '-';
	while (0 < i)
	{
		res[i] = base[x % 10];
		x = x / 10;
		i--;
	}
	res[j] = 0;
	return (res);
}

static char	*cispos(int c, char *res, int j, char *base)
{
	int				i;
	unsigned int	x;

	x = c;
	i = j - 1;
	while (0 <= i)
	{
		res[i] = base[x % 10];
		x = x / 10;
		i--;
	}
	res[j] = 0;
	return (res);
}

char	*ft_itoa(int c)
{
	char		*base;
	char		*res;
	// int			i;
	int			j;
	long int	x;

	j = nbr(c);
	base = "0123456789";
	// i = j - 1;
	x = c;
	res = (char *)malloc((j * sizeof(char)) + 1);
	if (!res)
		return (NULL);
	if (x < 0)
		return (cisneg(c, res, j, base));
	else
		return (cispos(c, res, j, base));
	return (res);
}
