/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 22:31:57 by aohssine          #+#    #+#             */
/*   Updated: 2024/11/09 21:27:16 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsdup(char **base)
{
	int		i;
	char	**strs;

	if (!base || !(*base))
		return (NULL);
	i = -1;
	strs = malloc(sizeof(char *) * ft_strslen(base) + 1);
	if (!strs)
		return (NULL);
	while (base[++i])
		strs[i] = ft_strdup(base[i]);
	strs[i] = NULL;
	return (strs);
}
