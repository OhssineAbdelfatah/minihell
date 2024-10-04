#include"../../includes/minishell.h"

int update_env(t_env **head, char *key, char *env_main)
{
    t_env *tmp ;
    tmp = *head;
    char *value;
    char *check;

    while(tmp != NULL)
    {
        if(ft_strcmp(tmp->key, key) == 0){
            value = ft_strchr(env_main ,'=');
            if(value != NULL)
            {
                value++;
                check = ft_strdup(value);
                if(!check || check[0] == '\0'){
                    free(check);
                    return 0;
                }
                tmp->value = check;
                tmp->valid = true;
            }
            return 0;
        }
        tmp = tmp->next;
    }
    return 1 ;
}

char *clean_arg(char *args)
{
    char *dup = ft_strdup(args);
    int i = -1;
    int j = 0;
    
    while(args && dup && args[++i] && dup[j]){
        while(dup[j] == '\'' || dup[j] == '"')
            j++;
        if(!dup[j])
            break;
        args[i] = dup[j];
        j++;
    }
    args[i] = 0;
    free(dup);
    return args;
}

t_env *add_env(char *env_main, t_env *ennv)
{
    char *value;
    t_env *node;
    char **key;

    node = malloc(sizeof(t_env));
    if(!node)
        return NULL;
    node->next = NULL;

    key = ft_split(env_main, '=');
    if(!key || ft_strslen(key) == 0)
        return NULL;
    if(!update_env(&ennv, key[0],env_main)) // env_main sould be a value // to do
        return NULL;
    node->key = ft_strdup(key[0]);
    free_split(key);

    value = ft_strchr(env_main ,'=');
    node->value = NULL;
    node->valid = false;
    if(value != NULL)
    {
        value++;
        node->value = ft_strdup(value);
        node->valid = true;
    }

    return node;
}

void print_export(t_env *env)
{
    while(env != NULL)
    {
        printf("declare -x %s=\"",env->key);
        if(env->value)
            printf("%s",env->value);
        printf("\"\n");
        env = env->next;
    }
}

void export(t_env **ennv,char **cmd)
{
    char **cmd_args;
    t_env *tmp;
    int i;

    i = -1 ;
    while(cmd[++i])
        cmd[i] = clean_arg(cmd[i]);
    i = ft_strslen(cmd);
    if(i == 1){
        print_export(*ennv);
        return ;
    }
    i = 0;
    while(cmd[++i]){
        tmp = add_env(cmd[i],*ennv);
        add_back_env(ennv,tmp);
    }
    (void)cmd_args;
}
