#include"../../includes/minishell.h"

void print_env(t_env *env)
{
    while(env != NULL)
    {
        if(env->key && env->value && env->valid == true)
            printf("%s=%s\n",env->key,env->value);
        env = env->next;
    }
}

void add_back_env(t_env **head, t_env*node)
{
    t_env *tmp;
    if(node == NULL)
        return ;
    if(!head )
        return;
    if(!(*head)){
        *head = node;
        return ;
    }
    tmp = *head;
    while(tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = node;
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
    node->valid = false;
    if(value != NULL)
    {
        value++;
        node->value = ft_strdup(value);
        node->valid = true;
    }
    node->next = NULL;
    return node;
}

t_env *init_env(char **env_main)
{ 
    t_env *env; // list head
    t_env *tmp; // used to head each node
    int i = -1;
    env =NULL;
    while(env_main[++i])
    {
        tmp = creat_env(env_main[i]); // create node 
        add_back_env(&env,tmp);
    }
    return env;
}