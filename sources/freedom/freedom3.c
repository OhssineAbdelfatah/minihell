/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:54:06 by ilaasri           #+#    #+#             */
/*   Updated: 2024/11/09 15:54:08 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_dawgs(int how_many, ...)
{
	int		i;
	char	**dawg;
	va_list	lst;

	i = 0;
	dawg = NULL;
	va_start(lst, how_many);
	while (i < how_many)
	{
		dawg = va_arg(lst, char **);
		free_mynigga(dawg);
		i++;
	}
	va_end(lst);
}
