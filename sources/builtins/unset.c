#include"../../includes/minishell.h"

void destroy_single_env(t_env *node)
{
    // puts(node->key);
    free(node->key);
    free(node->value);
    free(node);
}

void unset_env(t_env **head, char **key)
{
    t_env *tmp;
    int i ;
    t_env *tmp1;

    if(!head || !(*head))
        return ;
    tmp = *head;
    tmp1 = NULL;
    i = 0;
    while(key[++i])
    {
        if(ft_strcmp(tmp->key , key[i]) && ft_isalpha( key[i][0] ))
        {
            tmp1 = tmp;
            tmp = tmp->next ;
            destroy_single_env(tmp1);
            return ;
        }else if(ft_isdigit( key[i][0] )){
            printf("bash: unset: `%s': not a valid identifier\n",key[i]);
            continue;
        }
        while(tmp != NULL)
        {
            if(ft_strcmp(tmp->key , key[i]) && ft_isalpha( key[i][0] ))
            {
                destroy_single_env(tmp);
                tmp1->next = tmp1->next->next;
                  return ;
            }else if(ft_isdigit( key[i][0] )){
                printf("bash: unset: `%s': not a valid identifier\n",key[i]);
                continue;
            }
            tmp1 = tmp;
            tmp = tmp->next ;
        }
    }
}