#include "../includes/minishell.h"

int is_pipe(char *s)
{
    if (ft_strlen(s) == 1 && s[0] == '|')
        return(1);
    return(0);
}

t_cmd *parse_exec(char **tokens, int *i, char **env)
{
    t_cmd *res;
    struct exec_cmd *p;
    char *argv;

    res = NULL;
    if (RED == which_one(tokens[*i]))
        return NULL;
    argv = ft_strdup(tokens[*i]);
    // res = (t_cmd *)init_exec(EXEC,argv, env);


    p = (struct exec_cmd *)init_exec(EXEC,argv, env);
    printf("CMD :%s\n", p->argv);
    res = (t_cmd *)p;
    (*i)++;
    return(res);
}

t_cmd *parse_redirect(char **tokens, int *i, char **env)
{
    t_cmd *res;
    int fd;
    int mode;
    char *file;

    res = NULL;
    fd = 1;
    // write(1, "al\n", 4);
    // if (tokens[*i] && (which_one(tokens[*i]) != RED))
    res = parse_exec(tokens, i, env);
    while (tokens[*i] && (which_one(tokens[*i]) == RED))
    {
        if ( 1 == ft_strcmp(tokens[*i], ">>"))
            mode = 77;
        else if (ft_strcmp(tokens[*i], ">"))
            mode = 7;
        else if (ft_strcmp(tokens[*i], "<"))
        {
            mode = 4;
            fd = 0;
        }
        (*i)++;
        file = ft_strdup(tokens[*i]);
        (*i)++;
        res = init_redire(res, file, mode, fd);
    }
    return (res);
}

struct cmd *parse_pipe(char **tokens, int *i, char **env)
{
    t_cmd *res;

    // res = parse_redirect(tokens, i, env);
    res = parse_new_exec(tokens, i, env);
    while(tokens[*i] && is_pipe(tokens[*i]))
    {
        (*i)++;
        // res = (t_cmd *)init_pipe(res, parse_redirect(tokens , i, env));
        res = (t_cmd *)init_pipe(res, parse_new_exec(tokens , i, env));
    }
    return (res);
    
}


// t_cmd *parse_herdoc(char **tokens, int *i, char **env)
// {
//     t_cmd *res;

//     res = init_herdoc()
// }

// t_cmd *parse_commands(char **tokens, int *i, char **env)
// {
//     t_cmd *res = NULL;
//     t_cmd *right= NULL;
//     int  fd,mode, j;
//     char *file;
    
//     while(tokens[*i])
//     {
//         fd = 1;
//         if (!res)
//             res = parse_exec(tokens, i, env);
//         if (ft_strcmp(tokens[*i], "|"))
//         {
//             printf("left type%d\n", res->type);
//             (*i)++;
//             j = *i;
//             if (res->type == EXEC || res->type == PIPE)
//                 right = parse_exec(tokens, i, env);
//             else
//                 right = parse_commands(tokens, i, env);
//             res = (t_cmd *)init_pipe(res,right);
//         }
//         if(which_one(tokens[*i]) == RED)
//         {
//             if ( 1 == ft_strcmp(tokens[*i], ">>"))
//                 mode = 77;
//             else if (ft_strcmp(tokens[*i], ">"))
//                 mode = 7;
//             else if (ft_strcmp(tokens[*i], "<"))
//             {
//                 mode = 4;
//                 fd = 0;
//             }
//             (*i)++;
//             file = ft_strdup(tokens[*i]);
//             (*i)++;
//             res = init_redire(res, file, mode, fd);
//         }
//         if (which_one(tokens[*i]) == HERDOC)
//         {
//             (*i)++;
//             file = ft_strdup(tokens[*i]);
//             (*i)++;
//             res = init_herdoc(res, file);
//             herdoc_content(res);
//         }
//     }
//     return (res);
// }

t_cmd *parse_new_exec(char **tokens, int *i, char **env)
{
    t_cmd *res;
    // struct mew_cmd *p;
    t_red *redirect;
    char *argv;
    int x;

    res = NULL;
    x = *i;
    argv = cmd_line(tokens, i);
    redirect = get_red(tokens, x);
    res = (t_cmd *)init_new_cmd(argv, env, redirect);

    // printf("CMD :%s\n", p->argv);
    // res = (t_cmd *)p;
    printf("i:%d\n", *i);
    printf("argv content : %s\n", argv);
    printf("argv cmd : %p\n", &(*argv));
    // (*i)++;

    return(res);
}

t_cmd *root(char **tokens, char **env)
{
    int i = 0;
    t_cmd *res;

    res = NULL;
    // printf("creat root\n");
    res = parse_pipe(tokens, &i, env);
    printf("root addr:%p\n", &(*res));
    // printf("root addr:%p\n", &(*(res->argv)));
    
    // res = parse_new_exec(tokens, &i, env);
    // res = parse_commands(tokens, &i, env);
    // printf("roottype:%d\n", res->type);
    return(res);
}