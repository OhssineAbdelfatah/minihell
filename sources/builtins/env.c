#include"../../includes/minishell.h"

int print_env(t_env *env)
{
    while(env != NULL)
    {
        if(env->key && env->value )
            printf("%s=%s\n",env->key,env->value);
        env = env->next;
    }
    return 0;
}

void add_back_env(t_env **head, t_env*node)
{
    t_env *tmp;
    if(node == NULL)
        return ;
    if(!head )
        return;
    if(*head == NULL){
        *head = node;
        return ;
    }
    tmp = *head;
    while(tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = node;
    node->next = NULL;
}



t_env *creat_env(char *env_main)
{
    t_env *node;
    node = malloc(sizeof(t_env));
    if(!node)
        return NULL;

    char **key;
    key = ft_split(env_main, '=');
    node->key = ft_strdup(key[0]);
    free_split(key);

    char *value;
    value = ft_strchr(env_main ,'=');
    node->value = NULL;
    if(value != NULL)
    {
        value++;
        node->value = ft_strdup(value);
    }
    node->next = NULL;
    return node;
}

// int is_str_in(char *s1, char *s2)
// {

// }


t_env *init_env(char **env_main)
{ 
    t_env *env; // list head
    t_env *tmp; // used to head each node
    int i = -1;
    env = NULL;
    while(env_main && env_main[++i])
    {
        if (ft_strnstr(env_main[i], "OLDPWD", 6) == NULL)
        {
            tmp = creat_env(env_main[i]); // create node 
            add_back_env(&env,tmp);
        }
    }
    return env;
}