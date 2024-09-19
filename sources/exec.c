#include "../includes/minishell.h"

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
//OLD EXECUTE_PIPE:

void execute_pipe(t_cmd *cmd)
{
    struct pipe *pcmd;
    struct pipe *pcmd_right;
    struct new_cmd *cmd_child;
    int p[2];

    pcmd = (struct pipe *)cmd;
    if(pipe(p) < 0)
        panic("pipe");
    //LEFT CHILD COMMAND:
    if(fork() == 0)
    {
        cmd_child = (struct new_cmd *)pcmd->left;
        if (pcmd->pipe_fd != -1)
            cmd_child->fd_in = pcmd->pipe_fd;
        cmd_child->fd_out = p[1];
        close(p[0]);
        new_exec(pcmd->left);
    }
    //RIGHT CHILD COMMAND:
    if(fork() == 0)
    {
        cmd_child = (struct new_cmd *)pcmd->right;
        if (pcmd->right->type == PIPE)
        {
            pcmd_right = (struct pipe *)pcmd->right;
            pcmd_right->pipe_fd = p[0];
            close(p[1]);
            new_exec(pcmd->right);
            exit(0);
        }
        else
        {
            if (pcmd->pipe_fd != - 1)
                close(pcmd->pipe_fd);
            cmd_child->fd_in = p[0];
            close(p[1]);
            new_exec(pcmd->right);
        }
    }
    close(p[0]);
    close(p[1]);
    wait(0);
    wait(0);
} 
