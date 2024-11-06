#include "../../includes/minishell.h"

char *getEnvValue(t_env *env, char *key)
{
    while(env != NULL)
    {
        if(ft_strcmp(env->key, key))
            return env->value;
        env = env->next;
    }
    return NULL;
}

int check_is_abs(char *cmd)
{
    if(access(cmd, X_OK) == 0)
        return 0;
    return 1;
}

void append_slash(char **path_2d)
{
    int j = -1 ;
    char *tmp;

    while(path_2d[++j])
    {
        tmp = path_2d[j];
		path_2d[j] = ft_strjoin(tmp, "/");
        free(tmp);
        tmp = NULL;
    }
    return ;
}

char *cmd_abs_path(char *path,char *cmd)
{
    char **path_2d;
    char *tmp;
    char *cmd_abs_path;
    int i = -1;

    path_2d = ft_split(path, ':');
    cmd_abs_path = cmd;
    append_slash(path_2d);
    while(path_2d[++i])
    {
        tmp = ft_strjoin(path_2d[i], cmd_abs_path);
        if(access(tmp, X_OK) == 0)
        {
            cmd_abs_path = tmp;
            free_mynigga(path_2d);
            return cmd_abs_path;
        }
        free(tmp);
        tmp = NULL;
    }
    free_mynigga(path_2d);
    return NULL;
}

