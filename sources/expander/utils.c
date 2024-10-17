#include"../../includes/minishell.h"

char *ft_name(char *arg)
{
    if(!arg)
        return NULL;
    arg++;
    while(*arg){
        if( (!ft_isalnum(*arg) && *arg != '_' && *arg!= '?') || *arg == '\0')
            return arg;
        arg++;
    }
    return arg;
}

void free_lst(t_node *head)
{
    t_node * tmp;

    while(head){
        tmp = head->next;
        debug_free(head->str);
        debug_free(head);
        head = tmp;
    }
}

char *clean_qts(char *str)
{
    char *new;
    if((int)ft_strlen(str) < 3)
        new = ft_strdup("");
    else
        new = ft_strndup(str+1,ft_strlen(str+1)-1);
    debug_free(str);
    return new;
}