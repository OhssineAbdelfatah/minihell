#include "../includes/minishell.h"

void ft_swap_str(char **s1,char **s2)
{
    char *tmp;

    tmp = *s1;
    *s1 = *s2;
    *s2 = tmp;
}


char *join_cmd(char *s1, char *s2)
{
    int i;
    int reslen;
    char *res;

    reslen = ft_strlen(s1) + ft_strlen(s2);
    if(NULL != s1)
        reslen += 1;
    res = (char *)malloc(reslen + 1);
    int l= ft_strlen(s1);
    i = 0;
    while(i < l)
    {
        res[i] = s1[i];
        i++;
    }
    if (l > 0)
        res[i] = 32;
    i++;
    l = 0;
    while ((size_t)l < ft_strlen(s2))
        res[i++] = s2[l++];
    res[i] = 0;
    free(s1);
    return (res);
    
}

char *cmd_line(char **tokens, int *x)
{
    int i, j;
    t_typenode ref;
    char *cmd;

    i = *x;
    ref = EXEC;
    cmd = NULL;
    while (tokens[i])
    {
        j = which_one(tokens[i]);
        if (PIPE == j)
            break;
        if (ref == RED || ref == HERDOC )
           { ref = FILE_NAME;}
        else if (FILE_NAME == ref)
           { ref = EXEC;}
        if (j == RED || j == HERDOC)
          {  ref = j;}
        if (ref == EXEC)
        {
            // cmd = ft_strdup(tokens[i]);
            if (NULL == cmd)
                cmd = ft_strdup(tokens[i]);
            else
                cmd = join_cmd(cmd , tokens[i]);
        }
        i++;
    }
    *x = i;
    return(cmd);
}

int get_mode(char **tokens, int i)
{
    if (ft_strcmp(tokens[i], "<"))
        return (4);
    if (ft_strcmp(tokens[i], ">>"))
        return(77);
    if (ft_strcmp(tokens[i], ">"))
        return(7);
    return (0);
}

int get_type(char **tokens, int i)
{
    if (ft_strcmp(tokens[i], "<<"))
        return (HERDOC);
    return (RED);
}

void do_nothing(int signal)
{
    // printf("^C");
    return;
}


void get_content(t_red *red_lst,char *del, int *heredoc_pipe)
{
     char *str;
    int p[2];
    int pid;
    int pid_status;
    // struct sigaction sa_old, sa_ignore;
    // sa_ignore.sa_handler = SIG_IGN;
    // sigaction(SIGINT, &sa_ignore, &sa_old);
    (void)red_lst;

    if (*heredoc_pipe != -1)
    {
        dprintf(2,"closing this pipe:%d\n", *heredoc_pipe);
        close(*heredoc_pipe);
    }
    pipe(p);
    pid = fork();
    if(0 == pid)
    {
        signal(SIGINT, NULL);
        // printf("from child:p[0]:%d, p[1] : %d\n", p[0], p[1]);
        while(1)
        {
            str = readline(">");
            if (ft_strcmp(str, del))
                break;
            ft_putstr_fd(str, p[1]);
            ft_putstr_fd("\n", p[1]);
        }
        close(p[1]);
        close(p[0]);
        exit(0);
    }
    else if (pid > 0)
    {
        // struct sigaction sa_ignore, sa_old;
        // sa_ignore.sa_handler = SIG_IGN;  // Ignore SIGINT
        // sigaction(SIGINT, &sa_ignore, &sa_old);  // Set the ignore handler

        // int status;
        // // waitpid(pid, &status, 0);  // Wait for the child process to finish

        // // Restore the original SIGINT handler in the parent
        // sigaction(SIGINT, &sa_old, NULL);
        signal(SIGINT, do_nothing);
        pid_status =  waitpid(pid, NULL,0);
        signal(SIGINT, signal_handler);
      
        if (pid_status != -1)
            *heredoc_pipe = p[0];
        else
            close(p[0]);
        close(p[1]);
    }
    
    // printf("assign fd_in of herdoc:%d\n", *heredoc_pipe);
    return;
}


t_red *get_red(char **tokens, int i, int *herdoc_pipe)
{
    t_red *red_lst;
    char *delimiter;

    red_lst = NULL;
    while (tokens[i] && PIPE != which_one(tokens[i]))
    {
        if (which_one(tokens[i]) == RED || HERDOC == which_one(tokens[i]))
        {
            if (NULL == red_lst)
                red_lst = creat_red_lst(tokens, i);
            else
                add_to_lst(red_lst, tokens, i);
            if (!red_lst)
                return(NULL);
            if (HERDOC == which_one(tokens[i]))
            {
                i++;
                delimiter = ft_strdup(tokens[i]);
                get_content(red_lst, delimiter,herdoc_pipe);
                i--;
            }
            i++; 
        }
        i++;
    }
    return (red_lst);
}