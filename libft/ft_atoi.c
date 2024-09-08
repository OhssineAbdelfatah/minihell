/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 21:53:48 by ilaasri           #+#    #+#             */
/*   Updated: 2023/12/24 04:38:36 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	passspace(const char *str, int i)
{
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	long	res;
	int		i;
	int		sign;
	long	tmp;

	i = 0;
	sign = 1;
	res = 0;
	i = passspace(str, i);
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			sign *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		tmp = res;
		res = res * 10 + (str[i++] - 48);
		if (tmp != res / 10 && sign == 1)
			return (-1);
		if (tmp != res / 10 && sign == -1)
			return (0);
	}
	return (res * sign);
}
