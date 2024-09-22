#include "../includes/minishell.h"

int is_pipe_next(char **tok, int i)
{
    while (tok[i])
    {
        if(ft_strcmp(tok[i], "|"))
            return (1);
        i++;
    }
    return (0);
}
void pipe_try(char **tok)
{
    int i;
    int p[2];

    pipe(p);


    return;
}

// void execute(char *s)
// {
//     char *cmd;

//     cmd = ft_strjoin("/usr/bin/",s);
//     execve(cmd, NULL, NULL);
//     exit(0);
// }

void get_herdoc(char **tokens,int i, t_herdoc *herdoc);

// int main(int ac , char **av)
// {
//     if (ac != 2)
//         return 1 ;
//     char **tok;
//     t_herdoc *doc;

//     tok = fr9_trb7(av[1]);
//     doc = (t_herdoc *)malloc(sizeof(t_herdoc));
//     doc->herdoc_pipe = 0;
//     doc->to_exp = 0;
//     // get_herdoc(tok, 0, doc);
//     printf("to_exp :%d, herdoc_pipe : %d\n", doc->to_exp, doc->herdoc_pipe);
//     change_herdoc_int(doc);
//     printf("to_exp :%d, herdoc_pipe : %d\n", doc->to_exp, doc->herdoc_pipe);
//     return 0;
// }