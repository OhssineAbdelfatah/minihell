#include"../../includes/minishell.h"

t_node *create_node(char *value, char type)
{
    t_node *node = debug_malloc(sizeof(t_node));
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

void mini_expander(t_node **head, t_env *env, int *st)
{
    t_node *tmp;
    char *tmpstr;

    tmp = *head ;
    while(tmp){
        // delete single or double
        if(tmp->type == 'w' || tmp->type == 'd'){
            tmpstr = tmp->str;   
            tmp->str =  splitWordVar(tmp->str, env, st);
            if(tmpstr != tmp->str)
                free(tmpstr);
        }
        tmp = tmp->next;
    }
    return ;
}

/*
char *splitWordVar(char *value, t_env *env){
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
            node = create_node(ft_strdup(value), '0');
            add_node( &head, &tail, node);
            break;     
        }
    }
    dollar = expand(&head, env);
    free_lst(head);
    return (dollar);
} 
*/

//char *dt.start; // start
//char *dt.token; // token

char *splitWordVar(char *value, t_env *env ,int *st)
{
    t_split_arg dt;

    dt.head = NULL;
    while(value){
        dt.start = ft_strchr(value, '$'); 
        if(dt.start && *(dt.start+1)){

            dt.token = ft_strndup(value, dt.start - value);
            dt.node = create_node(dt.token, '0');
            add_node( &dt.head, &dt.tail, dt.node);
            dt.token = ft_strndup(dt.start  , ft_name(dt.start ) - dt.start );
            if(ft_strlen(dt.token) == 1 && *dt.token == '$')
                dt.node = create_node(dt.token, '0');
            else
                dt.node = create_node(dt.token, '1');
            add_node( &dt.head, &dt.tail, dt.node);
            value = ft_name(dt.start) ;
        }
        else{
            dt.node = create_node(ft_strdup(value), '0');
            add_node( &dt.head, &dt.tail, dt.node);
            break;     
        }
    }
    return expand(&dt.head, env, st);
}
/*
char *expand(t_node **head, t_env *env)
{
    t_node *tmp;
    char *new;
    char *value;
    char *tmpstr;
    tmp = *head;
    while (tmp)
    {

        if (tmp->type == '1')
        {
            value = getEnvValue(env, tmp->str + 1);
            if(ft_strcmp(tmp->str + 1, "?"))
                value = "sandwich piknik !! la mayo"; // 
            // free(tmp->str);
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
        tmpstr = new ;
        new = ft_strjoin(new, tmp->str);
        free(tmpstr);
        tmp = tmp->next;
    }
    free_lst(*head);
    return new;
}
*/

char *expand(t_node **head, t_env *env, int *st)
{
    t_expn dt;
    dt.tmp = *head;
    while (dt.tmp)
    {
        if (dt.tmp->type == '1')
        {
            dt.value = getEnvValue(env, dt.tmp->str + 1);
            if(ft_strcmp(dt.tmp->str + 1, "?")){
                free( dt.value);
                dt.value = ft_itoa(*st); // 
            }
            dt.tmpstr = dt.tmp->str;
            dt.tmp->str = ft_strdup(dt.value);
            free(dt.tmpstr);
        }
        dt.tmp = dt.tmp->next;
    }
    dt.tmp = *head;
    dt.new = ft_strdup("");
    while (dt.tmp)
    {
        dt.tmpstr = dt.new ;
        dt.new = ft_strjoin(dt.new, dt.tmp->str);
        free(dt.tmpstr);
        dt.tmp = dt.tmp->next;
    }
    return (free_lst(*head), dt.new);
}