#include "../includes/minishell.h"


// void builtin(char **str, struct exec_cmd *p)
// {
//     if (ft_strcmp(str[0], "exit"))
//          panic("BY!\n");
//     // if (ft_strcmp(str[0], "cd"))
//     //     _cd_cmd(str, p);
//     // else if (ft_strcmp(str[0], "echo"))
//     //     _echo_cmd(str, p);
//     // else if (ft_strcmp(str[0], "exit"))
//     //     panic("BY!");
//     // else if (ft_strcmp(str[0], ""))
//     //     _export_cmd (str, p);
// }

int dstr_len(char **s)
{
    int i;

    i = 0;
    if (s)
    {
        while(s[i])
            i++;
    }
    return(i);
}

void execute_cmd(t_cmd *cmd)
{
    struct exec_cmd *p;
    char **str;
    char **argv;
    char *ss;
    // pid_t pid;

   
    p = (struct exec_cmd *)cmd;
    ss = ft_strdup(p->argv);
    if(!ss)
        return;
    str = ft_split(ss, 32);
    argv = ft_split(ss, 32);
    // builtin(str, p);
    free(ss);
    ss = NULL;
    if (dstr_len(str))
        ss = ft_strjoin("/usr/bin/",str[0]);
    // pid = fork();
    // if(0 == pid)
    // {
        if(-1 == execve(ss, str++,p->env))
        {
            free(ss);
            ss = ft_strdup(argv[0]);
            if (-1 == execve(ss, argv++,p->env))
            {
                printf("minishell: %s command not found\n", ss);
                panic("");
            }
        }
        free_mynigga(argv);
        free(ss);
        ss = NULL;
    // }
    wait(0);
    return;
}

void execute_red (t_cmd *cmd)
{
    struct red *p;
    int new_fd= 0;

    p = (struct red *)cmd;

    printf("the fd : %d, mode %d, file %s\n", p->fd, p->mode, p->file);
    // // struct exec_cmd *po = (struct exec_cmd *)p->cmd;
    // printf("the cmd :%s\n", po->argv);
    printf("exec red\n");

    if (p->mode == 77)
        new_fd = open(p->file, O_WRONLY | O_CREAT | O_APPEND, 0777);
    else if (p->mode == 7)
        new_fd = open(p->file,  O_WRONLY | O_CREAT| O_TRUNC, 0777);
    else if (p->mode == 4)
        new_fd = open(p->file, O_RDONLY, 0777);   
    if( new_fd < 0)
    {
        // fprintf(2, "open %s failed\n", p->file);
        panic("execred\n");
        exit(1);
    }
    // if ()make
    if (NULL != p->cmd)
    {
        close(p->fd);
        dup2(p->fd, new_fd);
        exec(p->cmd);
     }
    // wait(0);
    // open(1);
    // dup2(new_fd, p->fd);
    // close(new_fd);
}

void execute_heredoc(t_cmd *cmd)
{
    struct heredoc *p;

    p = (struct heredoc *)cmd;
    

}
 
void execute_pipe (t_cmd *cmd)
{
    struct pipe *pcmd;
    int p[2];

    pcmd = (struct pipe *)cmd;
    if(pipe(p) < 0)
      panic("pipe");
    if(fork() == 0){
      close(1);
      dup(p[1]);
      close(p[0]);
      close(p[1]);
      exec(pcmd->left);
    }
    if(fork() == 0){
      close(0);
      dup(p[0]);
      close(p[0]);
      close(p[1]);
      exec(pcmd->right);
    }
    close(p[0]);
    close(p[1]);
    wait(0);
    wait(0);
    // printf("exec PIPE\n");
} 

void exec(t_cmd *cmd)
{
    // write(1, "exec IN\n", 9);
    // printf("cmd type :%d\n", cmd->type);
    if (!cmd)
        return;
    else if (cmd->type == EXEC)
        execute_cmd (cmd);
    else if (cmd->type == PIPE)
        execute_pipe(cmd);
    else if (cmd->type == RED)
        execute_red (cmd);
    else if (cmd->type== HERDOC)
        execute_heredoc(cmd);
}



