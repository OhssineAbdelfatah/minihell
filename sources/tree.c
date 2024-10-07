#include "../includes/minishell.h"

int which_time;

int get_end_sub(char **tokens, int i)
{
    int res , ref;
    
    res= get_next_parenties_d(tokens, i);
    ref =  which_one (tokens[res + 1]) ;
    if (ref == RED || ref == HERDOC)
    {
        while (ref == RED || ref == HERDOC || ref == EXEC)
        {
            ref =  which_one (tokens[res + 1]) ;
            res++;
        }
    }
    else
        return(res +1);
    return res;
}

int is_pipe(char *s)
{
    if (ft_strlen(s) == 1 && s[0] == '|')
        return(1);
    return(0);
}

int is_and_or(char *s)
{
    if (ft_strlen(s) == 2)
    {
        if (s[0] == '&' && s[1] == '&')
            return AND;
        if (s[0] == '|' && s[0] == '|')
            return OR;
    }
    return -1;
}


//PARSE NEW_EXEC
/******************************************** */

t_cmd *parse_new_exec(char **tokens, int *i, t_env *env)
{
    t_cmd *res;
    t_red *redirect;
    t_herdoc *herdoc;
    char *argv;
    char **argv1;
    int x;

    res = NULL;
    x = *i;
    herdoc = (t_herdoc *)malloc(sizeof (*herdoc));
    if (!herdoc)
        panic("malloc failed\n");
    herdoc->herdoc_pipe = -1;
    herdoc->to_exp = 0;
    get_herdoc(tokens, x, herdoc);
    argv = cmd_line(tokens, i);
    argv1 = fr9_trb7(argv);
    free(argv);
    redirect = get_red(tokens, x, herdoc);
    res = (t_cmd *)init_new_cmd(argv1, env, redirect, herdoc);
    return(res);
}

/***************************************************************** */
//PARSE_SUB
/*********************************************************** */

struct cmd * parse_sub(char **tokens, int *i, t_env *myenv)
{
    t_cmd *res, *sub_root;
    t_red *redirect;
    t_herdoc *herdoc;
    int end_sub;
    int x;

    res = NULL;
    x = *i;
    herdoc = (t_herdoc *)malloc(sizeof (*herdoc));
    if (!herdoc)
        panic("malloc failed\n");
    end_sub = get_end_sub(tokens, *i);
    herdoc->herdoc_pipe = -1;
    herdoc->to_exp = 0;
    get_herdoc(tokens, *i, herdoc);
    (*i)++;
    sub_root = parse_and_or(tokens, i, myenv);
    redirect = get_red_for_sub(tokens, x);
    *i = end_sub;
    res = (t_cmd *)init_sub(sub_root, myenv, redirect,herdoc);
    return (res);
}

/*********************************************************** */

//PARSE PIPE WITH RECURSION :
/********************************************************* */
struct cmd *parse_pipe_rec(char **tokens, int *i, t_env *myenv)
{
    t_cmd *res;

    res = parse_new_exec(tokens, i, myenv);
    if  (tokens[*i] && is_pipe(tokens[*i]))
    {
        (*i)++;
        res = (t_cmd *)init_pipe(res, parse_pipe_rec(tokens , i, myenv));
    }
    return (res);  
}

/***************************************************************************** */


//PARSE IT WITH WHILE LOOP:
/************************************************************************ */

t_cmd *parse_pipe_loop(char **tokens, int *i, t_env *myenv)
{
    t_cmd *res;

    if (tokens[*i] && which_one(tokens[*i]) == S_SUB)
        res = parse_sub(tokens, i, myenv);
    else if (tokens[*i] && (which_one(tokens[*i]) == EXEC || which_one(tokens[*i]) == HERDOC || which_one(tokens[*i]) == RED))
        res = parse_new_exec(tokens, i, myenv);
    while  (tokens[*i] && is_pipe(tokens[*i]))
    {
        (*i)++;
        if (tokens[*i] && which_one(tokens[*i]) == S_SUB)
            res = (t_cmd *)init_pipe(res, parse_sub(tokens , i, myenv));
        else if (tokens[*i] && which_one(tokens[*i]) == EXEC)
            res = (t_cmd *)init_pipe(res, parse_new_exec(tokens , i, myenv));
    }
    return (res);
}

/************************************************************************* */

//PARSE AND | OR

/************************************************************************* */

t_cmd *parse_and_or(char **tokens, int *i, t_env *myenv)
{
    t_cmd *res;
    int ref;

    res = parse_pipe_loop(tokens, i, myenv);
    ref = is_and_or(tokens[*i]);
    while  (tokens[*i] && ref != -1)
    {
        if (ref == AND)
        {
            (*i) ++;
            res = (t_cmd *)init_and(res, parse_pipe_loop(tokens , i, myenv));
        }
        if (ref == OR)
        {
            (*i) ++;
            res = (t_cmd *)init_or(res, parse_pipe_loop(tokens , i, myenv));
        }
        ref = is_and_or(tokens[*i]);
    }
    return (res);
}

/*************************************************************************** */

t_cmd *root(char **tokens, t_env *env)
{
    int i = 0;
    t_cmd *res;
    // struct pipe *tmp;

    
    res = NULL;
    res = parse_and_or(tokens, &i, env);
    // printf("root TYPE %d\n", res->type);
    // if (res->type == PIPE)
    // {
    //     int i = 0;
    //     while (tokens[i])
    //         printf("%s\n", tokens[i ++]);
    //     tmp = (struct pipe *)res;
    //     printf("left:%d\n", tmp->left->type);
    //     printf("RIGHT:%d\n", tmp->right->type); 
    // }
    return(res);
}



// t_cmd *parse_sub(char **tokens, int *i,t_env *myenv)
// {
//     t_cmd *res;

//     (*i) ++;
//     res = parse_and_or(tokens, i, myenv);
//     (*i) ++;
//     return (res);
// }























































// t_cmd *parse_exec(char **tokens, int *i, char **env)
// {
//     t_cmd *res;
//     struct exec_cmd *p;
//     char *argv;

//     res = NULL;
//     if (RED == which_one(tokens[*i]))
//         return NULL;
//     argv = ft_strdup(tokens[*i]);
//     p = (struct exec_cmd *)init_exec(EXEC,argv, env);
//     res = (t_cmd *)p;
//     (*i)++;
//     return(res);
// }

// t_cmd *parse_redirect(char **tokens, int *i, char **env)
// {
//     t_cmd *res;
//     int fd;
//     int mode;
//     char *file;

//     res = NULL;
//     fd = 1;
//     // write(1, "al\n", 4);
//     // if (tokens[*i] && (which_one(tokens[*i]) != RED))
//     res = parse_exec(tokens, i, env);
//     while (tokens[*i] && (which_one(tokens[*i]) == RED))
//     {
//         if ( 1 == ft_strcmp(tokens[*i], ">>"))
//             mode = 77;
//         else if (ft_strcmp(tokens[*i], ">"))
//             mode = 7;
//         else if (ft_strcmp(tokens[*i], "<"))
//         {
//             mode = 4;
//             fd = 0;
//         }
//         (*i)++;
//         file = ft_strdup(tokens[*i]);
//         (*i)++;
//         res = init_redire(res, file, mode, fd);
//     }
//     return (res);
// }

struct cmd *parse_pipe(char **tokens, int *i, t_env **myenv)
{
    t_cmd *res;

    res = parse_new_exec(tokens, i, myenv);
    if  (tokens[*i] && is_pipe(tokens[*i]))
    {
        (*i)++;
        res = (t_cmd *)init_pipe(res, parse_pipe(tokens , i, myenv));
    }
    // printf("cmd is parsed\n");
    return (res);
    
}

t_cmd *parse_new_exec(char **tokens, int *i, t_env **env)
{
    t_cmd *res;
    t_red *redirect;
    t_herdoc *herdoc;
    char *argv;
    char **argv1;
    int x;
    int heredoc_pipe;

    res = NULL;
    x = *i;
    herdoc = (t_herdoc *)malloc(sizeof (*herdoc));
    if (!herdoc)
        panic("malloc failed\n");
    herdoc->herdoc_pipe = -1;
    herdoc->to_exp = 0;
    get_herdoc(tokens, *i, herdoc);
    argv = cmd_line(tokens, i);
    argv1 = fr9_trb7(argv);
    free(argv);
    redirect = get_red(tokens, x, herdoc);
    res = (t_cmd *)init_new_cmd(argv1, env, redirect, herdoc);
    return(res);
}

t_cmd *root(char **tokens, t_env **env)
{
    int i = 0;
    t_cmd *res;
    // struct pipe *p;
    // struct new_cmd *cmd;

    res = NULL;
    res = parse_pipe(tokens, &i, env);
    // if (res->type == PIPE)
    // {
    //     // p = (struct pipe *)res;
    //     // cmd = (struct new_cmd *)p->right;
    //     // printf("root heredoc pipe cmd :%d\n", cmd->);
    //     // printf("root type cmd :%d\n", cmd->type);
    //     // printf("root left cmd :%s\n", cmd->argv);
    //     // printf("root cmd :%d\n", p->left->type);
    //     // printf("root cmd :%d\n", res->type);
    // }
    return(res);
}
