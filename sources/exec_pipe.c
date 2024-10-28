#include "../includes/minishell.h"

/**********************************************************************************/
// THE MIGHTY PERFECT EXEC PIPE FUNCTION !!!
/**********************************************************************************/


void treat_left_child(t_cmd *left_cmd, t_execp *sp, int *last_status)
{
    (void)last_status;
    t_cmd_exec *left_one;
    t_sub_sh *left_sub;

    if (left_cmd->type == NEW_CMD)
    {
        left_one = (t_cmd_exec *)left_cmd;
        if (sp->node_p->pipe_fd != -1)
            left_one->fd_in =  sp->node_p->pipe_fd;
        left_one->fd_out = sp->p[1];
        close(sp->p[0]);
        exec_new_cmd(left_cmd, last_status);
        if (left_one->herdoc->herdoc_pipe > 0)
            close(left_one->herdoc->herdoc_pipe);
    }
    else
    {
        left_sub = (t_sub_sh *)left_cmd;
         if (sp->node_p->pipe_fd != -1)
            left_sub->fd_in =  sp->node_p->pipe_fd;
        left_sub->fd_out = sp->p[1];
        close(sp->p[0]);
        *last_status =  exec_sub_sh(left_cmd, last_status);
        if (left_sub->herdoc->herdoc_pipe > 0)
            close(left_sub->herdoc->herdoc_pipe);
        exit(*last_status);
    }
}

int right_child_ispipe(t_cmd *right_cmd , t_execp *sp, int *last_status)
{
    int status;
    t_pipe *right_pipe;

    (void)last_status;
    right_pipe = (t_pipe *)right_cmd;
    right_pipe->pipe_fd = sp->p[0];
    close(sp->p[1]);
    status = exec_pipe(right_cmd, last_status);
    return status;
}

int treat_right_child(t_cmd* right_cmd, t_execp *sp, int *last_status)
{
    int status;
    t_cmd_exec *right_one;
    t_sub_sh *right_sub; 

    (void)last_status;
    if (right_cmd->type == NEW_CMD)
    {
        right_one = (t_cmd_exec *)right_cmd;
        if (sp->node_p->pipe_fd != -1)
            close(sp->node_p->pipe_fd);
        right_one->fd_in = sp->p[0];
        close(sp->p[1]);
        status = exec_new_cmd(right_cmd, last_status);
        return status;
    }
    else if (right_cmd->type == SUB_SH)
    {
        right_sub = (t_sub_sh *)right_cmd;
        if (sp->node_p->pipe_fd != -1)
            close(sp->node_p->pipe_fd);
        right_sub->fd_in = sp->p[0];
        close(sp->p[1]);
        status = exec_sub_sh(right_cmd, last_status);
        return status;
    }
    return 0;
}

int exec_pipe(t_cmd *cmd, int *last_status)
{
    t_execp sp;

    if (pipe(sp.p) < 0)
        panic("PIPE FAILED !\n");
    sp.node_p = (t_pipe *)cmd;
    sp.lpid = fork();
    if (sp.lpid == 0)
        treat_left_child(sp.node_p->left, &sp, last_status);
    if (sp.node_p->right->type == PIPE)
        sp.status = right_child_ispipe(sp.node_p->right, &sp, last_status);
    else
    {
        sp.rpid = fork();
        if (sp.rpid == 0)
        {
            sp.status = treat_right_child(sp.node_p->right, &sp,last_status);
            exit(sp.status);
        }
    }
    close(sp.p[0]);
    close(sp.p[1]);
    signal(SIGINT, do_nothing);
    waitpid(sp.rpid , &(sp.status), 0);
    wait(0);
    return(sp.status);
}