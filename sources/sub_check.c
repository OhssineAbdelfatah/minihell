#include "../includes/minishell.h"

int is_there_cmd_after(char **tokens, int i)
{
    int ref, prev_ref;

    i++;
    if ( tokens[i] && which_one(tokens[i]) == S_SUB)
        return (1);
    while (tokens[i])
    {
        ref = which_one(tokens[i]);
        if (ref ==AND || ref == OR || ref == PIPE || ref == END_SUB)
            break;
        if (ref == EXEC)
        {
            if (prev_ref == HERDOC || prev_ref == RED)
                ref = FILE_NAME;
            else
                return (1); 
        }
        i++;
        prev_ref = ref;
    }
    return 0;
}


int is_there_cmd_before(char **tokens, int i)
{
    int ref;

    if (i == 0)
        return 1;
    i--;
    ref = which_one(tokens[i]);
    if (ref ==AND || ref == OR || ref == PIPE || ref == S_SUB)
        return (1);
    if (ref == HERDOC || ref == RED)
        return (1);
    if (ref == EXEC || ref == END_SUB)
        return (0);
    return 0;
}

int check_tok_sub(char **tokens)
{
    int ref, i;

    i = 0;
    while (tokens[i])
    {
        ref = which_one(tokens[i]);
        if (ref == S_SUB)
        {
            if (i > 0 && which_one(tokens[i - 1]) == EXEC)
                return (error(NULL, 40),7878);
            if ( tokens[i + 1] && which_one(tokens[i + 1]) != EXEC && which_one(tokens[i + 1]) != S_SUB)
                return (error(NULL, 41), 1008);
        }
        if (ref == END_SUB)
        {
            if (is_there_cmd_after(tokens, i))
                return (error(NULL, 41), 1008);
            if (is_there_cmd_before(tokens, i))
                return (error(NULL, 41), 1008);
        }
        i++;
    }
    return (0);
}
