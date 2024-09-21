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

// void print_node(t_env *nd){
//     if(!nd )
//         return ;
//     if(nd->key)
//         printf("key [%s] ", nd->key);
//     else
//         printf("key [null] ");
//     if(nd->value)
//         printf("value [%s] ", nd->value);
//     else
//         printf("value [null] ");
//     if(nd->valid)
//         printf("status [true]\n");
//     else
//         printf("status [false]\n");
// }

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


// void penv(t_env *env)
// {
//     while(env != NULL)
//     {
//         if(env->valid)
//             printf("%s\t","valid");
//         else
//             printf("%s\t","invalid");
//         printf("%s=",env->key);
//         if(env->value) 
//                 printf("%s",env->value);
//         printf("\n");
//         env = env->next;
//     }
// }

void export(t_env **ennv,char *cmd)
{
    char **cmd_args;
    t_env *tmp;
    int i;

    cmd = clean_arg(cmd);
    cmd_args = ft_split(cmd, ' ');
    i = ft_strslen(cmd_args);
    if(i == 1){
        print_export(*ennv);
        return ;
    }
    i = 0;
    while(cmd_args[++i]){
        tmp = add_env(cmd_args[i],*ennv);
        add_back_env(ennv,tmp);
    }
}

// int main(__unused int ac, __unused char **av, char *ennv[])
// {

//     t_env *myenv;
//     myenv = init_env(ennv);
//     print_env(myenv);
//     unset_env(&myenv, av[1]);
//     puts("");
//     puts("");
//     puts("");
//     puts("");
//     puts("");
//     print_env(myenv);
// }

/*
    export :
        - export => should print declare -x key="value"
        - export key="value" key=value => should add key=value to env linked list as valid env(valid == true)
        - export keya= | keyb => should add keyb(valid==false) and keya(valid=true) to env 
*/

/*
    valid :
        export key=
        export key="value" (value without double/single qoutes)
        export key=value
    invalid :
        export key* (without =)
*/