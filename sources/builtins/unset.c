#include"../../includes/minishell.h"

void destroy_single_env(t_env *node)
{
    free(node->key);
    free(node->value);
    free(node);
}

void unset_env(t_env **head, char *key)
{
    t_env *tmp;

    tmp = *head;
    while(tmp->next->next != NULL)
    {
        if(ft_strcmp(tmp->next->key , key) == 0){
            destroy_single_env(tmp->next);
            tmp->next = tmp->next->next;
            return ;
        }
        tmp = tmp->next ;
    }
}