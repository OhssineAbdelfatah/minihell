#include "../includes/minishell.h"

int g_sig;

void debug_free(void *ptr)
{   
    // printf(G"freed addrs[%p]\n"CRESET,ptr);
    if(ptr)
        free(ptr);
}

void *debug_malloc(size_t size)
{   
    void *ptr;
    ptr = malloc(size);
    if(!ptr)
        return NULL;
    // printf(R"Allocate [%zu] addrs [%p]\n"CRESET,size,ptr);
    return ptr;
}


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
    (void)str;
    if (str)
        ft_putstr_fd(str, 2);
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
        {
            // signal (SIGINT, NULL); 
            exec_new_cmd(cmd ,&status);
        }
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
    if (g_sig == -1)
        *status = new_exec(res, NOTHING, status);
    if (g_sig == 130)
    {
        *status = 130;
        g_sig = -1;
    }
    // printf(GRN"D exit STATUS :%d\n"CRESET, *status);
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

// void ff(){
//     system("leaks minishell");
// }

int main(  int ac, char **av, char **env)
{
    char *str;
    int status;
    char **my_tokens;
    t_env *dup_env;
    int checker ;   

    // atexit(ff);
    status = 0;
    dup_env = init_env(env);
    while(1)
    {
        signal(SIGINT, signal_handler);
        signal(SIGQUIT, SIG_IGN);
        str = readline(GRN"depechez-vous!> "CRESET);
        history(str);
        if (g_sig == 1300)
        {
            // printf("Status : %d\n", status);
            status = 1;
        }
        g_sig = -1;
        if (str && ft_strlen(str) && _check_str(str) == 0)
        {
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
    (void)ac;
    (void)av;
}
