#include"../../includes/minishell.h"

// int update_env(t_env **head, char *key, char *env_main)
// {
//     t_env *tmp ;
//     tmp = *head;
//     char *value;
//     char *check;

//     while(tmp != NULL)
//     {
//         if(ft_strcmp(tmp->key, key) == 0){
//             value = ft_strchr(env_main ,'=');
//             if(value != NULL)
//             {
//                 value++;
//                 check = ft_strdup(value);
//                 if(!check || check[0] == '\0'){
//                     free(check);
//                     return 0;
//                 }
//                 tmp->value = check;
//                 tmp->valid = true;
//             }
//             return 0;
//         }
//         tmp = tmp->next;
//     }
//     return 1 ;
// }

void update_env(t_env *node, char *value)
{
    debug_free(node->value);
    node->value = value;
    return ;
}


// char *clean_arg(char *args)
// {
//     char *dup = ft_strdup(args);
//     int i = -1;
//     int j = 0;
    
//     while(args && dup && args[++i] && dup[j]){
//         while(dup[j] == '\'' || dup[j] == '"')
//             j++;
//         if(!dup[j])
//             break;
//         args[i] = dup[j];
//         j++;
//     }
//     args[i] = 0;
//     free(dup);
//     return args;
// }

// t_env *add_env(char *env_main, t_env **ennv)
// {
//     char *value;
//     t_env *node;
//     char **key;

//     node = malloc(sizeof(t_env));
//     if(!node)
//         return NULL;
//     node->next = NULL;

//     key = ft_split(env_main, '=');
//     if(!key )
//         return NULL;
//     if(!update_env(ennv, key[0],env_main)) // env_main sould be a value // to do
//         return NULL;
//     node->key = ft_strdup(key[0]);
//     free_split(key);

//     value = ft_strchr(env_main ,'=');
//     node->value = NULL;
//     node->valid = false;
//     if(value != NULL)
//     {
//         value++;
//         node->value = ft_strdup(value);
//         node->valid = true;
//     }

//     return node;
// }

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
        return arg;
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
    node = debug_malloc(sizeof(t_env));
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
    cmd = expander(cmd, *ennv);
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
                update_env(tmp, value);
                free(key);
            }else
            {
                tmp = creat_new_env(key, value);
                add_back_env(ennv, tmp);
            }
        }else if(!is_valid(key)){
            status  = 1;
            printf("bash: export: `%s': not a valid identifier\n" ,cmd[i]);
        }
    }
    return status;
}
