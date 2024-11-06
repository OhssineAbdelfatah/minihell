#include "../../includes/minishell.h"


int last_herdoc(t_red *lst)
{
    t_red *tmp;
 
    if (lst)
    {
        tmp = lst->next;
        while(tmp)
        {
            if (tmp->type == HERDOC)
                return(0);
            tmp = tmp->next;
        }
    }
    return(1);
}



void open_herdoc(t_red *redirect, int *std[3],t_herdoc *herdoc, t_env *env)
{
    if (*std[0] != -1 && last_herdoc(redirect))
        close(*std[0]);
    if (last_herdoc(redirect))
    {
        *std[0] = herdoc->herdoc_pipe;
        if(!herdoc->to_exp)
            *std[0] = herdoc_newfd( herdoc->herdoc_pipe, env);
    }
}


int     exec_red(t_red *redirect, int *std[4], t_herdoc *herdoc, t_env *env)
{
    int status;
    t_red *tmp;

    status = 0;
    tmp = redirect->next;
    //     /*test segv 102*/
    // printf("here");
    // exit(0);
    // /*test segv 102*/
    while(redirect)
    {
        tmp = redirect->next;
        status = open_file(redirect, std, herdoc, env);
        redirect = tmp;
    }
    return(status);
}



int check_red(t_cmd_exec  *p , int *ref, int *last_status)
{
    int status;
    int *std[4];

    status = 0;
    std[1] = &(p->fd_out);
    std[0] = &(p->fd_in);
    std[2] = ref;
    std[3] = last_status;

    if (NULL != p->redirect)
        status = exec_red(p->redirect, std, p->herdoc ,*(p->myenv));
    if (status)
        return(status);
    if (p->fd_in != -1 || p->fd_out != -1)
    {
        if (p->fd_out != -1)
        {
            p->std_out = dup(1);
            dup2(*std[1], 1);
            close(*std[1]);
        }
        if(p->fd_in != -1)
        {
            p->std_in = dup(0);
            dup2(*std[0], 0);
            close(*std[0]);
        }
    }
    return (status);
}
