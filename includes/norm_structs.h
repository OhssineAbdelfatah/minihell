/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:17:50 by ilaasri           #+#    #+#             */
/*   Updated: 2024/10/29 14:17:54 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NORM_STRUCT_H
# define NORM_STRUCT_H

typedef struct s_without_quotes t_without_quotes;


struct s_without_quotes
{
    char	*res;
	int res_len;
    int i;
    int j;
    int end;
};

#endif