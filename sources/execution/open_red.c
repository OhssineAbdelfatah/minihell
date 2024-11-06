#include "../../includes/minishell.h"

void check_err_red(t_red *redirect ,char *file_name, int *std[2])
{
    if (ft_strlen(file_name) == 0)
            panic("minishell: no such file or directory!\n");
        //her to expand name of file 
        if (*std[1] != -1 && (77 == redirect->mode || 7== redirect->mode))
            close(*std[1]);
        if (*std[0] != -1 && 4 == redirect->mode)
            close(*std[0]);
}

void open_input_file(t_red *redirect, int *std[3], t_env *env)
{
    // (void)env;
    redirect->file = expand_filename(redirect->file, env, 0, RED_EXPN);
    redirect->file = wild_expand_red(redirect->file, *std[2]);
    // check filename isNotEmpty
    *std[0] = open(redirect->file, O_RDONLY);
    if (*std[0] < 0)
    {
        dprintf(2,"minishell: %s:No such file or directory!\n", redirect->file);
        panic("");
    }
    return ;
}

int open_outfile_trunc(t_red *redirect, int *std[3], t_env *env, char *file_name)
{
    // (void)env;
    redirect->file = expand_filename(redirect->file, env,0 ,RED_EXPN);
    redirect->file = wild_expand_red(redirect->file, *std[2]);
    // check filename isNotEmpty
    if (!redirect->file)
        return (free(file_name), 1);
    *std[1] = open(redirect->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
    return 0;
}

void open_file_append(t_red *redirect, int *std[3], t_env *env)
{
    // (void)env;
    redirect->file = expand_filename(redirect->file, env,0, RED_EXPN);
    redirect->file = wild_expand_red(redirect->file, *std[2]);
    // check filename isNotEmpty
    *std[1] = open(redirect->file, O_RDWR | O_CREAT | O_APPEND, 0644);
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
        check_err_red(redirect, file_name,  std);
        if (77 == redirect->mode)
            open_file_append(redirect, std, env);
        else if (7== redirect->mode)
            status = open_outfile_trunc(redirect, std, env, file_name);
        else if (4== redirect->mode)
            open_input_file(redirect, std, env);
        if (*std[1] < 0 && 4 != redirect->mode && !(redirect->file) )// 
        {
            dprintf(2,"minishell: %s: Permission denied\n", redirect->file);
            free(redirect->file);
            panic("");
        }
    }
    free(file_name);
    return(status);
}