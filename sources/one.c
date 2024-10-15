#include "../includes/minishell.h"

int sig;

int check_qoutes(char *s)
{
    int i;
    enum ss j;

    i = 0;
    j = NONE;
    if (s)
    {
        while(s[i])
        {
            if(s[i] == '"')
            {
                if (j == SINGLE)
                    j = SINGLE;
                else if (j == DOUBLE)
                    j = NONE;
                else
                    j = DOUBLE;
            }
            if(s[i] == '\''){
                
                if (j == DOUBLE)
                    j = DOUBLE;
                else if (j == SINGLE)
                    j = NONE;
                else
                    j = SINGLE;
            }
            i++;
        }
    }
    return(j);
}

void panic(char *str)
{
    if (str)
        dprintf(2, "%s", str);
    exit(1);
}


void execute(t_cmd *cmd)
{
    int status;
    status = 0;
    if (cmd->type == NEW_CMD && is_builtin(cmd))
        status = exec_builtin(cmd);
    else if (cmd->type == NEW_CMD )
    {
        status = fork();
        if (status == 0)
            exec_new_cmd(cmd ,&status);
        wait(&status);
        // printf("status d'exit:%d\n", status);
    }
    else
        status = new_exec(cmd , NOTHING, &status);

}

void parse_nd_exec(char **my_tokens,t_env **dup_env, int *status)
{
    t_cmd *res;
    
    res = NULL;

    res = root(my_tokens,dup_env);
    if (!res)
        return;
    // print_tree(res);
    // printf("\n");
    if (sig == -1)
        *status = new_exec(res, NOTHING, status);
    if (sig == 130)
    {
        *status = 130;
        sig = -1;
    }
    printf(GRN"exit STATUS :%d\n"CRESET, *status);
    free_mynigga(my_tokens);
    free_tree2(res); 
}


void history(char *str)
{
    if (!str)
        panic("BY\n");
    if (!str || 0 == ft_strlen(str))
        return ;
    if (is_white_str(str))
        return;
    add_history(str);

}

int main(  int ac, char **av, char **env)
{
    char *str;
    int status;
    char **my_tokens;
    t_env *dup_env;
    int checker ;   

    (void)av;
    (void)ac;
    status = 0;
    dup_env = init_env(env);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
    while(1)
    {
        sig = -1;
        str = readline(GRN"depechez-vous!> "CRESET);
        history(str);
        if (ft_strlen(str) && _check_str(str) == 0)
        {
            signal(SIGQUIT, SIG_DFL);
            my_tokens = fr9_trb7(str);
            checker = _check_tokens(my_tokens);
            if (checker != EXEC && checker != SUB_SH)
            {
                free_mynigga(my_tokens);
                error(NULL,checker);
                status = 258;
            }
            else if (my_tokens)
                parse_nd_exec(my_tokens, &dup_env, &status);
            // printf("SIG :%d\n", sig);
            // printf("status AT the very end :%d\n", status);
        }
        free(str);
    }
}
