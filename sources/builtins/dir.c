#include"../../includes/minishell.h"

int pwd(t_cmd *cmd)
{
    t_ncmd  *p;
    p = (t_ncmd *)cmd;
    char *curd = NULL;
    printf("%s\n",getcwd(curd, 1024));
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
    t_ncmd *p;
    p = (t_ncmd *)cmd;
    char *arg;
    // cd only without args
    if(ft_strslen(p->argv) == 1){ 
        if( !(arg = getEnvValue(p->myenv ,"HOME")) )
            return -1;
        chdir(arg);
    }else
    {
        if(access(p->argv[1], R_OK) != 0)
            return -1;
        chdir(p->argv[1]);
    }
     return 0;   
}