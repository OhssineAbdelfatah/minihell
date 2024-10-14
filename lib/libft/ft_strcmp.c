/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 00:16:14 by aohssine          #+#    #+#             */
/*   Updated: 2024/09/20 00:36:50 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int     ft_strcmp(char *s1, char *s2)
{
        int i, s2len;

        i = 0;
        s2len = ft_strlen(s2);
        if (!s1 || !s2)
                return (0);
        else
        {
        while(i < s2len)
        {
            if (s1[i] != s2[i])
                return(0);
            i++;
        }
        if ((size_t)s2len != ft_strlen(s1))
            return(0);
    }
    return(1);
}