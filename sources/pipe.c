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
