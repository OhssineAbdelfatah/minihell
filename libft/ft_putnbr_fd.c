/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:12:39 by ilaasri           #+#    #+#             */
/*   Updated: 2023/12/16 22:53:20 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	x;
	char		*base;

	x = n;
	base = "0123456789";
	if (x < 0)
	{
		ft_putchar_fd('-', fd);
		x *= -1;
	}
	if (x < 10)
	{
		ft_putchar_fd(base[x], fd);
	}
	if (x >= 10)
	{
		ft_putnbr_fd((x / 10), fd);
		ft_putchar_fd(base[x % 10], fd);
	}
}
