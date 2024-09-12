#include"../../includes/minishell.h"

int env_size(t_env *root)
{
    int i =0;
    while(root){
        i++;
        root = root->next;
    }
    return i;
}

char **lstoarry(t_env *root)
{
    char **env_arr;
    char *single_env;
    int env_len = env_size(root);
    int i = -1;
    if(env_len == 0)
        return NULL;
    env_arr = malloc(sizeof(char *) * (env_len + 1) );
    if (!env_arr)
        return (NULL);
    while(++i < env_len)
    {
        single_env = ft_strjoin(root->key,"=");
        single_env = ft_strjoin(single_env, root->value);
        env_arr[i] = ft_strdup(single_env);
        free(single_env);
        root = root->next;
    }
    env_arr[i] = NULL;  
    return env_arr;
}

// int main(int ac, char **av, char**env){
//     t_env* myenv= init_env(env);
//     char **env_arr = lstoarry(myenv);
//     int i = -1;
//     while(env_arr[++i])
//         printf("%s\n",env_arr[i]);
// }