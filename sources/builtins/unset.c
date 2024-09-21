#include"../../includes/minishell.h"

void destroy_single_env(t_env *node)
{
    // puts(node->key);
    free(node->key);
    free(node->value);
    free(node);
}

void unset_env(t_env **head, char *key)
{
    t_env *tmp;
    t_env *tmp1;

    tmp = *head;
    tmp1 = NULL;
    while(tmp != NULL)
    {
        if(ft_strcmp(tmp->key , key))
        {
            puts(tmp->key);
            puts(tmp1->next->key);
            puts(tmp1->next->next->key);
            destroy_single_env(tmp);
            tmp1->next = tmp1->next->next;
              return ;
        }
        tmp1 = tmp;
        tmp = tmp->next ;

    }
}