/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 23:09:04 by ilaasri           #+#    #+#             */
/*   Updated: 2024/11/09 23:09:06 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	my_dprint(int fd, char *s, ...)
{
	va_list	lst;
	int		i;

	i = 0;
	va_start(lst, s);
	while (s[i])
	{
		if (s[i] == '%' && s[i + 1] == 's')
		{
			ft_putstr_fd(va_arg(lst, char *), fd);
			i++;
		}
		else
			write(fd, &s[i], 1);
		if (s[i])
			i++;
	}
	va_end(lst);
}
// hadi ghi bach nvisualisiw chejra dyalna a batal

// void print_red(t_red *tmp)
// {
//     // t_red *tmp =  p->redirect;
//     while (NULL != tmp)
//     {
//         if (tmp->mode == 77)
//             printf(" >> ");
//         if (tmp->mode == 7)
//             printf(" > ");
//         if (tmp->mode == 4)
//             printf(" < ");
//         if (tmp->type == HERDOC)
//             printf(" << ");
//         printf("%s", tmp->file);
//         tmp = tmp->next;
//     }
// }

// void print_tree(t_cmd *res)
// {
//     t_cmd_exec  *p1;
//     t_pipe  *p2;
//     t_and  *p3;
//     t_or *p4;
//     t_sub_sh  *p5;
//     int i = 0;

//     if (NULL == res)
//         return ;
//     if (res->type == NEW_CMD)
//     {
//         p1 = (t_cmd_exec *)res;
//         if (p1->argv == NULL)
//             printf("'NULL'");
//         else
//         {
//             while (p1->argv[i])
//                 printf(" %s", p1->argv[i++]);
//         }
//         if (NULL != p1->redirect)
//             print_red(p1->redirect);
//         // if (NULL != p1->herdoc)
//         //     printf("  d_p:%d",p1->herdoc->herdoc_pipe);
//         // printf("");
//     }
//     else if (res->type == PIPE)
//     {
//         p2 = (t_pipe  *)res;
//         printf("[");
//         print_tree(p2->left);
//         printf(" |");
//         print_tree(p2->right);
//         printf("]");
//     }
//     else if (res->type == AND)
//     {
//         p3 = (t_and  *)res;
//         printf("[");
//         print_tree(p3->left);
//         printf(" &&");
//         print_tree(p3->right);
//         printf("]");
//     }
//     else if (res->type == OR)
//     {
//         p4 = (t_or *)res;
//         printf("[");
//         print_tree(p4->left);
//         printf(" ||");
//         print_tree(p4->right);
//         printf("]");
//     }
//     else if (res->type == SUB_SH)
//     {
//         p5 = (t_sub_sh  *)res;
//         printf("(");
//         print_tree(p5->sub_root);
//         printf(")");
//         if (NULL != p5->redirect)
//             print_red(p5->redirect);
//     }
// }
