#include"../../includes/minishell.h"

t_node *create_node(char *value, char type)
{
    t_node *node = malloc(sizeof(t_node));
    node->str = value;
    node->type = type;
    node->next = NULL;
    return node;
}

void add_node(t_node **head, t_node **tail, t_node *node)
{
    if (*head == NULL) {
        *head = node;
    } else {
        (*tail)->next = node;
    }
    *tail = node;
}

void mini_expander(t_node **head, t_env *env)
{
    t_node *tmp;
    tmp = *head ;
    while(tmp){
        // delete single or double
        if(tmp->type == 'd' || tmp->type == 's')
            tmp->str = clean_qts(tmp->str);
        if(tmp->type == 'w' || tmp->type == 'd')
            tmp->str =  splitWordVar(tmp->str, env);
        tmp = tmp->next;
    }
    return ;
}


char *splitWordVar(char *value, t_env *env)
{
    t_node *head;
    t_node *tail;
    t_node *node;
    char *dollar;
    char *bdollar;

    head = NULL;
    while(value){
        dollar = ft_strchr(value, '$'); 
        if(dollar && *(dollar+1)){

            bdollar = ft_strndup(value, dollar - value);
            node = create_node(bdollar, '0');
            add_node( &head, &tail, node);
            // free(bdollar);
            
            bdollar = ft_strndup(dollar  , ft_name(dollar ) - dollar );
            if(ft_strlen(bdollar) == 1 && *bdollar == '$')
                node = create_node(bdollar, '0');
            else
                node = create_node(bdollar, '1');
            add_node( &head, &tail, node);
            value = ft_name(dollar) ;
            // free(bdollar);
        }
        else{
            node = create_node(value, '0');
            add_node( &head, &tail, node);
            break;     
        }
    }
    if (head == NULL)
        return value;
 
    return expand(&head, env);
} 

char *expand(t_node **head, t_env *env)
{
    t_node *tmp;
    char *new;
    char *tmpp;
    char *value;
    tmp = *head;
    while (tmp)
    {

        if (tmp->type == '1')
        {
            value = getEnvValue(env, tmp->str + 1);
            free(tmp->str);
            if (value)
                tmp->str = ft_strdup(value);
            else
                tmp->str = ft_strdup("");
        }
        tmp = tmp->next;
    }
    tmp = *head;
    new = ft_strdup("");
    while (tmp)
    {
        tmpp = new;
        new = ft_strjoin(new, tmp->str);
        free(tmpp);
        tmp = tmp->next;
    }
    // free_lst(*head);
    return new;
}
