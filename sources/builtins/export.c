#include"../../includes/minishell.h"


void update_env(t_env *node, char *value)
{
    node->value = value;
    return ;
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
char *getKey(char* arg)
{
    char *eql;
    eql = ft_strchr(arg, '=');
    if(!eql)
        return ft_strdup(arg);
    eql = ft_strndup(arg, eql - arg);
    return eql;
}

char *getValue(char* arg)
{
    char *eql;

    eql = ft_strchr(arg, '=');
    if(!eql )
        return NULL;
    eql = ft_strdup(eql+1);
    return eql;
}

t_env *env_exist(char *key, t_env* node)
{
    while(node != NULL)
    {
        if(ft_strcmp(node->key, key))
            return node;
        node = node->next;
    }
    return NULL;
}

t_env* creat_new_env(char *key, char *value)
{
    t_env *node;
    node = malloc(sizeof(t_env));
    if(!node)
        return NULL;

    node->key = key;
    node->value = value;
    return node;
}
int export(t_env **ennv,char **cmd)
{
    int status ;
    t_env *tmp;
    char *key;
    char *value;
    int i;

    tmp = NULL;
    status = 0;
    if(ft_strslen(cmd) == 1)
        return (print_export(*ennv), status);
    i = 0;
    while(cmd[++i])
    {
        // printf("cmd %s\n", cmd[i]);
        key = getKey(cmd[i]);
        if(key && is_valid(key)){
            tmp = env_exist(key, *ennv);
            value = getValue(cmd[i]);
            if(tmp){
                tmp->value = value;
                free(key);
            }else
            {
                tmp = creat_new_env(key, value);
                add_back_env(ennv, tmp);
            }
        }else if(!is_valid(key)){
            status  = 1;
            printf("bash: export: `%s': not a valid identifier\n" ,cmd[i]);
            free(key);
        }
    }
    return status;
}
