#include "../../includes/minishell.h"

int check_err_red(t_red *redirect ,char *file_name, int *std[3])
{
    if (ft_strlen(file_name) == 0)
    {
        ft_putstr_fd("minishell: no such file or directory!\n",2);
        if (*std[2])
            exit (1);
        return (free(file_name), 1);
    }
        //her to expand name of file 
    if (*std[1] != -1 && (77 == redirect->mode || 7== redirect->mode))
        close(*std[1]);
    if (*std[0] != -1 && 4 == redirect->mode)
        close(*std[0]);
    return 0;
    // free(file_name);
}

int open_input_file(t_red *redirect, int *std[3], t_env *env)
{
    redirect->file = expand_filename(redirect->file, env, 0, RED_EXPN);
    if (!redirect->file)
        return (1);
    redirect->file = wild_expand_red(redirect->file, *std[2]);
    if (!redirect->file)
        return (1);
    // check filename isNotEmpty
    *std[0] = open(redirect->file, O_RDONLY);
    if (*std[0] < 0)
    {
        dprintf(2,"minishell: %s:No such file or directory!\n", redirect->file);
        if (*std[2])
            panic("");
        return 1;
    }
    return  0;
}

int open_outfile_trunc(t_red *redirect, int *std[3], t_env *env)
{
    // (void)env;
    // check filename isNotEmpty
    redirect->file = expand_filename(redirect->file, env,0 ,RED_EXPN);
    if (!redirect->file)
        return (1);
    redirect->file = wild_expand_red(redirect->file, *std[2]);
    if (!redirect->file)
        return (1);
    *std[1] = open(redirect->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
    // printf("FD>>%d\n", *std[1]);
    return 0;
}

int open_file_append(t_red *redirect, int *std[3], t_env *env)
{
    // (void)env;
    redirect->file = expand_filename(redirect->file, env,0, RED_EXPN);
     if (!redirect->file)
        return (1);
    redirect->file = wild_expand_red(redirect->file, *std[2]);
    // check fil"ename isNotEmpty
    *std[1] = open(redirect->file, O_RDWR | O_CREAT | O_APPEND, 0644);
    return (0);
}

int open_file(t_red *redirect,int *std[3], t_herdoc *herdoc, t_env *env)
{
    int status;
    status = 0;
    char *file_name1 , *file_name;

    file_name1 = ft_strdup(redirect->file);
    file_name = whithout_quotes(file_name1);
    if (HERDOC==redirect->type)
        open_herdoc(redirect, std, herdoc, env);
    else
    {
        if (check_err_red(redirect, file_name,  std))
            return (1);
        if (77 == redirect->mode)
        {
           status =  open_file_append(redirect, std, env);
            if (status == 1)
                return (free(file_name), status);
       }
        else if (7== redirect->mode)
        {
            status = open_outfile_trunc(redirect, std, env);
            // printf("<FD :>>%d\n", *std[1]);
            if (status == 1)
                return (free(file_name), status);
        }
        else if (4== redirect->mode)
        {
            status = open_input_file(redirect, std, env);
            if (status == 1)
                return (free(file_name), status);
        }
        if (*std[1] < 0 && 4 != redirect->mode)// 
        {

            dprintf(2,"minishell: %s: Permission denied\n", redirect->file);
            // free(redirect->file);
            // ft_putstr_fd("ATAY\n", 2);
            if (*std[2] != SIMPLE)
                panic("");
            else 
                return (free(file_name),1);
        }
    }
    free(file_name);
    return(status);
}
