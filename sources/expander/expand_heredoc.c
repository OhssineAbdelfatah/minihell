#include"../../includes/minishell.h"

int herdoc_newfd( int fd, t_env* myenv)
{ 
    char *line ;
    char *tmp ;
    int fd_pipe[2];

    pipe(fd_pipe);
    while(1)
    {
        line = get_next_line(fd);
        if(!line)
            break;
        tmp = line;
        line = splitWordVar(line, myenv, 0);
        free(tmp);
        if(line)
            ft_putstr_fd(line, fd_pipe[1]);
        else
            ft_putstr_fd("\n", fd_pipe[1]);
        free(line);
        free(NULL);
    }   
    line = get_next_line(-1);
    close(fd_pipe[1]);
    close(fd);
    return fd_pipe[0];
}

char *expand_filename(char *filename, t_env *env,int *last_status ,int source)
{   
    if(!filename || (filename && filename[0] == '\0'))
        ambiguous_exit(filename, source);
    if(ft_strchr(filename, '$') == NULL)
        return filename;

    char *new = splitWordVar(filename, env, last_status);
    if(!new || count_arg(new) != 1){
        ambiguous_exit(filename, 0);
        free(new);
        free(filename);
        return NULL;
    }
    return new;
}
