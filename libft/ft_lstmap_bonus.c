/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 01:51:39 by ilaasri           #+#    #+#             */
/*   Updated: 2023/12/19 22:01:45 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*s;
	t_list	*d;
	t_list	*newnode;
	void	*cont;

	s = NULL;
	d = NULL;
	if (!f || !lst || !del)
		return (NULL);
	while (lst)
	{
		cont = (*f)(lst->content);
		newnode = ft_lstnew(cont);
		if (!newnode)
		{
			del(cont);
			ft_lstclear(&s, del);
			return (NULL);
		}
		ft_lstadd_back(&s, newnode);
		lst = lst->next;
		d = s;
	}
	return (d);
}
