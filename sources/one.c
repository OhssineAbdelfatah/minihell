#include "../includes/minishell.h"

// int sig;

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

void free_mynigga(char **str)
{
    int i;
    
    i = 0;
    if (str)
    {
   
        while (str[i])
        {
            free(str[i]);
            str[i] = NULL;
            i++;
        }
    }
    free(str);
    str = NULL;
}

void execute(t_cmd *cmd, t_env *env)
{
    (void)env;
    int status;
    if (cmd->type == NEW_CMD)
    {
        status = fork();
        if (status == 0)
            exec_new_cmd(cmd);
        wait(&status);
        // printf("status d'exit:%d\n", status);
    }
    else
        status = new_exec(cmd);

}

void parse_nd_exec(char **my_tokens,t_env *dup_env)
{
    t_cmd *res;
    int status;
    
    res = NULL;
    if (ft_strcmp( my_tokens[0], "exit"))
        panic("BY!\n");
    res = root(my_tokens,dup_env);
    if (!res)
        return;
    // print_tree(res);
    // printf("\n");
    if (sig == -1)
        execute(res, dup_env);
    free_tree2(res);
}

void	signal_handler(int signal)
{
	int	status;

	status = 0;
	// (void)signal;
	wait(&status);
	printf("\n");
	rl_on_new_line();
	// rl_replace_line("", 0);
	// if (status && WIFSIGNALED(status) == TRUE)
	// 	g_vars->exit_status = WTERMSIG(status) + 128;
	// else
	rl_redisplay();
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
    char **my_tokens;
    t_env *dup_env;
   

    (void)av;
    (void)ac;
    dup_env = init_env(env);
	signal(SIGINT, signal_handler);
	// signal(SIGINT, do_nothing);
    while(1)
    {
        sig = -1;
        str = readline("depechez-vous!> ");
        history(str);
        my_tokens = NULL;
        if (0 !=_check_str(str))
        {
            printf("corrupt str:%s\n", str);
            panic("error from the main\n");
        }
        else if (ft_strlen(str))
        {
            my_tokens = fr9_trb7(str);
            if (my_tokens)
                parse_nd_exec(my_tokens, dup_env);
            free_mynigga(my_tokens);
        }
        free(str);
    }
}

// // GOAL EXEC THE REDIRECTION :