/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 01:40:56 by ilaasri           #+#    #+#             */
/*   Updated: 2023/12/24 06:01:16 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	reslen;

	// if (!s1 || !s2)
	// 	return (NULL);
	if (!s2)
		return (NULL);
	reslen = ft_strlen(s2) + ft_strlen(s1);
	res = (char *)malloc(sizeof(char) * (reslen + 1));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1, ft_strlen(s1) + 1);
	ft_strlcat((res), s2, reslen + 1);
	return (res);
}
