/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:11:43 by aohssine          #+#    #+#             */
/*   Updated: 2024/11/05 13:46:06 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000000
# endif
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include"../libft/libft.h"
char	*get_next_line(int fd);
// int		ft_strlen(char *s);
char	*join(char *s1, char *s2);
int		find_char(char *s, char c);
char	*trim_line(char *s);
char	*hold_grbg(char *s);
char	*ft_calloc_gnl(int count, int size);

#endif
