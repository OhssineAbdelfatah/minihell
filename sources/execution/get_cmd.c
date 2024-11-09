#include "../../includes/minishell.h"


// char *get_cmd(){

//     // if(check_is_abs(p->argv[0]) == 0)
//     //     abs_path = p->argv[0];
//     // else{   
//     //     abs_path = getEnvValue(*(p->myenv), "PATH");
//     //     if(!abs_path)
//     //         error_exec_new(p->argv[0], -1);
//     //     abs_path = cmd_abs_path(abs_path, p->argv[0]);
//     //     if(!abs_path )
//     //         error_exec_new(p->argv[0], 127);
//     // }
//     return NULL;
// }

void handle_error(t_cmd_exec *p, char **abs_path)
{
    struct stat file;

    if(p->argv[0] && (p->argv[0][0] == '/' || (p->argv[0][0] == '.' && p->argv[0][1] == '/') || (p->argv[0][0] == '.' && p->argv[0][1] == '.' && p->argv[0][2] == '/')))// is cmd starts with / or ./w
    {
        if(stat(p->argv[0], &file) == -1)//
        {
            write(2, "minishell: no such file or directory\n", 38);
		    exit(127) ;
        } else if(S_ISDIR(file.st_mode)){
            write(2, "minishell: "  ,11);
            write(2, p->argv[0]  ,ft_strlen(p->argv[0]));
            write(2, "is a directory\n",16);
            exit(126);
        } else if(S_ISREG(file.st_mode) && !(file.st_mode & S_IXUSR))
        {
            write(2, "minishell: permission denied\n", 30);
            exit(126);
        }
        else if (S_ISREG(file.st_mode) && file.st_mode & S_IXUSR){
            *abs_path = p->argv[0];
            return ;
        }
    }else{
        *abs_path = getEnvValue(*(p->myenv), "PATH");
        if(!(*abs_path))
            error_exec_new(p->argv[0], 1);
        *abs_path = cmd_abs_path(*abs_path, p->argv[0]);
        if(!abs_path )
            error_exec_new(p->argv[0], 127);
    }
}