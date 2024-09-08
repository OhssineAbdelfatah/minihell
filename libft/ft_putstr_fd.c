/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:55:40 by ilaasri           #+#    #+#             */
/*   Updated: 2023/12/16 15:55:50 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	slen;
	size_t	i;

	i = 0;
	slen = ft_strlen(s);
	while (i < slen)
	{
		write(fd, &s[i], 1);
		i++;
	}
}
