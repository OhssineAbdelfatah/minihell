/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strslen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 22:36:03 by aohssine          #+#    #+#             */
/*   Updated: 2024/09/05 22:36:41 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int ft_strslen(char **strs)
{
    int i = -1;
    if(!strs || !(*strs))
        return 0;
    while(strs[++i]);
    return i;
}