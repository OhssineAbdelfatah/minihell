#include "../includes/minishell.h"

int first_time;

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
int check_cmd_type(t_cmd *cmd)
{
    if (cmd->type == NEW_CMD)
        return(1);
    return(0);
}

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

// void execute_cmd(t_cmd *cmd)
// {
//     struct exec_cmd *p;
//     char **str;
//     char **argv;
//     char *ss;
//     // pid_t pid;

   
//     p = (struct exec_cmd *)cmd;
//     ss = ft_strdup(p->argv);
//     if(!ss)
//         return;
//     str = ft_split(ss, 32);
//     argv = ft_split(ss, 32);
//     // builtin(str, p);
//     free(ss);
//     ss = NULL;
//     if (dstr_len(str))
//         ss = ft_strjoin("/usr/bin/",str[0]);
//     // pid = fork();
//     // if(0 == pid)
//     // {
//         if(-1 == execve(ss, str++,p->env))
//         {
//             free(ss);
//             ss = ft_strdup(argv[0]);
//             if (-1 == execve(ss, argv++,p->env))
//             {
//                 printf("minishell: %s command not found\n", ss);
//                 panic("");
//             }
//         }
//         free_mynigga(argv);
//         free(ss);
//         ss = NULL;
//     // }
//     wait(0);
//     return;
// }

// void execute_red (t_cmd *cmd)
// {
//     struct red *p;
//     int new_fd= 0;

//     p = (struct red *)cmd;

//     printf("the fd : %d, mode %d, file %s\n", p->fd, p->mode, p->file);
//     // // struct exec_cmd *po = (struct exec_cmd *)p->cmd;
//     // printf("the cmd :%s\n", po->argv);
//     printf("exec red\n");

//     if (p->mode == 77)
//         new_fd = open(p->file, O_WRONLY | O_CREAT | O_APPEND, 0777);
//     else if (p->mode == 7)
//         new_fd = open(p->file,  O_WRONLY | O_CREAT| O_TRUNC, 0777);
//     else if (p->mode == 4)
//         new_fd = open(p->file, O_RDONLY, 0777);   
//     if( new_fd < 0)
//     {
//         // fprintf(2, "open %s failed\n", p->file);
//         panic("execred\n");
//         exit(1);
//     }
//     // if ()make
//     if (NULL != p->cmd)
//     {
//         close(p->fd);
//         dup2(p->fd, new_fd);
//         exec(p->cmd);
//      }
//     // wait(0);
//     // open(1);
//     // dup2(new_fd, p->fd);
//     // close(new_fd);
// }

// void execute_heredoc(t_cmd *cmd)
// {
//     struct heredoc *p;

//     p = (struct heredoc *)cmd;
    

// }
 
//OLD EXECUTE_PIPE:

void execute_pipe(t_cmd *cmd)
{
    struct pipe *pcmd;
    struct pipe *pcmd_right;
    int p[2];

    pcmd = (struct pipe *)cmd;
    if(pipe(p) < 0)
      panic("pipe");
    if(fork() == 0)
    {
        if (pcmd->pipe_fd != - 1)
        {
            close(0);
            dup(pcmd->pipe_fd);
        }
        close(1);
        dup(p[1]);
        printf("out from child left:%d\n", p[1]);
        close(p[0]);
        close(p[1]);
        new_exec(pcmd->left);
    }
    if(fork() == 0)
    {
        close(0);
        dup(p[0]);
        printf("in from child right:%d\n", p[0]);
        if (pcmd->right->type == PIPE)
        {
            close(1);
            pcmd_right = (struct pipe *)pcmd->right;
            pcmd_right->pipe_fd = p[1];
            dup(pcmd_right->pipe_fd);
        }
        close(p[0]);
        close(p[1]);
        new_exec(pcmd->right);
    }
    close(p[0]);
    close(p[1]);
    wait(0);
    wait(0);
} 


// void execute_pipe (t_cmd *cmd)
// {
//     first_time++;
//     struct pipe *pcmd;
//     pid_t pid1, pid2;
//     int p[2];
//     // printf("first time::%d\n", first_time);
//     pcmd = (struct pipe *)cmd;
//     if(pipe(p) < 0)
//       panic("pipe");
//     pid1 = fork();
//     if(pid1 == 0)
//     {
//     //   close(1);
//       dup2(p[1], 1);
//       close(p[0]);
//       close(p[1]);
//       new_exec(pcmd->left);
//     }
//     if (NEW_CMD == pcmd->right->type)
//         pid2= fork();
//     if(pid2 == 0)
//     {
//     //   close(0);
//         dup2( p[0], 0);
//         close(p[0]);
//         close(p[1]);
//         new_exec(pcmd->right);

//     }
//     else if (PIPE == pcmd->right->type)
//     {
//         dup2( p[0], 0);
//         close(p[0]);
//         close(p[1]);
//         new_exec(pcmd->right);
//     }
//     if (NEW_CMD == pcmd->right->type)
//             wait(pid2);
//     close(p[0]);
//     close(p[1]);
//     wait(pid1);
// } 



//TRY MINE
/*
void execute_pipe(t_cmd *cmd)
{
    struct pipe *pcmd;
    int pid1, pid2;
    int p[2];

    pcmd = (struct pipe*)cmd;
    pipe(p);
    pid1 = fork(); 
    if (pid1 == 0)
    {
        dup2(p[1],1);
        close(p[0]);
        close(p[1]);
        exec_new_cmd(pcmd->left);
    }
    if (NEW_CMD == pcmd->right->type)
        pid2 = fork();
    if (pid2 == 0)
    {
        dup2(p[0], 0);
        close(p[0]);
        close(p[1]);
        exec_new_cmd(pcmd->right);
    } 
    else if (PIPE == pcmd->right->type)
    {
        dup2(p[0], 0);
        close(p[0]);
        close(p[1]);
        execute_pipe(pcmd->right);
    } 
    if (NEW_CMD == pcmd->right->type)
    wait(pid1);
    wait(pid2);
    close(p[0]);
    close(p[1]);
}*/

/*
        |
      /   \
    ls     |
          
          / \
    
    wc -l    rev

*/


// void execute_pipe(t_cmd *cmd)
// {
//     struct pipe *pcmd;
//     int p[2];
//     pid_t pid1, pid2;
//     pcmd = (struct pipe *)cmd;
//     if (pipe(p) < 0)
//         panic("pipe");
//     // First child process (left side of the pipe)
//     if ((pid1 = fork()) == 0) {
//         close(1); // close stdout
//         if (dup(p[1]) < 0) 
//             panic("dup1"); // connect stdout to write end of pipe
//         close(p[0]); // close unused read end of pipe
//         close(p[1]); // close write end of pipe
//         new_exec(pcmd->left); // execute left command
//     }
//     else if (pid1 < 0) {
//         panic("fork");
//     }
//     // Second child process (right side of the pipe)
//     if ((pid2 = fork()) == 0) {
//         close(0); // close stdin
//         if (dup(p[0]) < 0)
//             panic("dup0"); // connect stdin to read end of pipe
//         close(p[0]); // close read end of pipe
//         close(p[1]); // close unused write end of pipe
//         new_exec(pcmd->right); // execute right command
//     }
//     else if (pid2 < 0) {
//         panic("fork");
//     }
//     // Parent closes both ends of the pipe
//     close(p[0]);
//     close(p[1]);
//     // Wait for both child processes
//     waitpid(pid1, NULL, 0);
//     waitpid(pid2, NULL, 0);
// }


// void execute_pipe (t_cmd *cmd)
// {
//     struct pipe *pcmd;
//     int id1, id2;
//     int p[2];

//     pcmd = (struct pipe *)cmd;
//     id1 = -1;
//     id2 = -1;
//     if (1 == check_cmd_type(pcmd->left))
//         id1 = fork();
//     if(id1 == 0)
//         new_exec(pcmd->left);
//     else if (id1 == -1)
//         new_exec(pcmd->left);
//     if (1 == check_cmd_type(pcmd->right))
//         id2 = fork();
//     if(id2 == 0)
//     {
//         new_exec(pcmd->right);
//     }
//     else if (-1 == id2)
//         new_exec(pcmd->right);
//     if (id1 >= 0)
//         wait(id1);
//     if (id2 >= 0)
//         wait(id2);
// } 



// void exec(t_cmd *cmd)
// {
//     // write(1, "exec IN\n", 9);
//     // printf("cmd type :%d\n", cmd->type);
//     if (!cmd)
//         return;
//     else if (cmd->type == EXEC)
//         execute_cmd (cmd);
//     else if (cmd->type == PIPE)
//         execute_pipe(cmd);
//     else if (cmd->type == RED)
//         execute_red (cmd);
//     else if (cmd->type== HERDOC)
//         execute_heredoc(cmd);
// }



