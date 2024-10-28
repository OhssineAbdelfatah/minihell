#include"../../includes/minishell.h"

int pwd(t_cmd *cmd)
{
    struct exec_cmd *p;

    p = (struct exec_cmd *)cmd;
    char *curd = NULL;
    curd = getcwd(curd, 0);
    if(!curd)
        return 1;
    printf("%s\n",curd);
    free(curd);
    curd = NULL;
    return 0;
}

// bool check_files(char **files)
// {
//     int i = 0;
//     while(files[++i]){
//         if(access(files[i], R_OK | X_OK | W_OK) != 0)
//             return false;
//     }
//     return true;
// }


// int cd(t_cmd *cmd)
// {
//    // i shoudld handle
//    /*
//    - : chdir to OLDPWD env variable if setted
//    ~ : chdir to HOME env variable
//    arg : pass directly to chdir
//    */
//     // char *curd = NULL;
//     // cast to exec_cmd
//     // printf("%s\n",getcwd(curd,1024));
//     t_cmd_exec  *p;
//     p = (t_cmd_exec  *)cmd;
//     char *arg;
//     p = (t_cmd_exec  *)cmd;
//     // cd only without args
//     if(ft_strslen(p->argv) == 1){ 
//         if( !(arg = getEnvValue(*(p->myenv) ,"HOME")) ){
//             printf("bash: cd: HOME not set\n");
//             return -1;
//         }
//         chdir(arg);
//     }else
//     {
//         if(access(p->argv[1], R_OK) != 0)
//             return -1;
//         chdir(p->argv[1]);
//     }
//     return 0;   
// }

static void update_oldpwd(t_new_cmd *p)
{
    t_env *tmp;

    char *working_dir ;
    working_dir = NULL;
    working_dir = getcwd(working_dir, 0);
    tmp = env_exist("OLDPWD",*(p->myenv));
    // create OLDPWD
    if(!tmp){
        tmp = creat_new_env(ft_strdup("OLDPWD") ,working_dir);
        add_back_env(p->myenv, tmp);
    }
    // update OLDPWD
    else
        update_env(tmp, working_dir);
}
static void update_pwd(t_new_cmd *p)
{
    t_env *tmp;

    char *working_dir ;
    working_dir = NULL;
    working_dir = getcwd(working_dir, 0);
    tmp = env_exist("PWD",*(p->myenv));
    // create OLDPWD
    if(!tmp){
        tmp = creat_new_env(ft_strdup("PWD") ,working_dir);
        add_back_env(p->myenv, tmp);
    }
    // update OLDPWD
    else
        update_env(tmp, working_dir);
}


int cd(t_cmd *cmd)
{
    t_new_cmd *p;
    char *arg;

    p = (t_cmd_exec *)cmd;
    if(ft_strslen(p->argv) == 1){ 
        if( !(arg = getEnvValue(*(p->myenv) ,"HOME")) ){
            printf("bash: cd: HOME not set\n");
            return -1;
        }
        chdir(arg);
    }else
    {
        if(access(p->argv[1], R_OK) != 0)
            return -1;
        update_oldpwd(p);
        chdir(p->argv[1]);
        update_pwd(p);
    }
    return 0;   
}