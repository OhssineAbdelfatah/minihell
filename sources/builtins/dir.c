#include"../../includes/minishell.h"

int pwd(t_cmd *cmd)
{
    struct exec_cmd *p;
    char *tmp;
    p = (struct exec_cmd *)cmd;
    char *curd = NULL;
    tmp = getcwd(curd, 1024);
    printf("%s\n",tmp);
    free(tmp);
    tmp = NULL;
    (void)p;
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


int cd(t_cmd *cmd)
{
   // i shoudld handle
   /*
   - : chdir to OLDPWD env variable if setted
   ~ : chdir to HOME env variable
   arg : pass directly to chdir
   */
    // char *curd = NULL;
    // cast to exec_cmd
    // printf("%s\n",getcwd(curd,1024));
    struct new_cmd *p;
    p = (struct new_cmd *)cmd;
    char *arg;
    p = (struct new_cmd *)cmd;
    // cd only without args
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
        chdir(p->argv[1]);
    }
     return 0;   
}