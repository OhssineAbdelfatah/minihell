#include "../includes/minishell.h"

int	check_cmd_type(t_cmd *cmd)
{
	if (cmd->type == NEW_CMD)
		return (1);
	return (0);
}

int	dstr_len(char **s)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
			i++;
	}
	return (i);
}

int	exec_and(t_cmd *cmd, int *last_status)
{
	t_and	*and_cmd;
	int		status;

	and_cmd = (t_and *)cmd;
	status = new_exec(and_cmd->left, AND, last_status);
	if (status == 0)
		status = new_exec(and_cmd->right, AND, last_status);
	return (status);
}

int	exec_or(t_cmd *cmd, int *last_status)
{
	t_or	*or_cmd;
	int		status;

	or_cmd = (t_or *)cmd;
	status = new_exec(or_cmd->left, OR, last_status);
	if (status != 0)
		status = new_exec(or_cmd->right, OR, last_status);
	return (status);
}

// OLD EXECUTE_PIPE:
/*************************************************************/
// EXEC PIPE IF IT WAS PARSED WITH RECURSION :
/*************************************************************/
// int execute_pipe(t_cmd *cmd)
// {
//     t_pipe  *pcmd;
//     t_pipe  *pcmd_right;
//     t_cmd_exec  *cmd_child;
//     int p[2];
//     int pid2, pid1, status;

//     status = 0;
//     pcmd = (t_pipe  *)cmd;
//     if(pipe(p) < 0)
//         panic("pipe");
//     //LEFT CHILD COMMAND:
//     pid1 = fork();
//     if(pid1 == 0)
//     {
//         cmd_child = (t_cmd_exec  *)pcmd->left;
//         if (pcmd->pipe_fd != -1)
//             cmd_child->fd_in = pcmd->pipe_fd;
//         cmd_child->fd_out = p[1];
//         close(p[0]);
//         new_exec(pcmd->left, PIPE);
//         if (cmd_child->herdoc->herdoc_pipe > 0)
//         {
//             printf("%d\n",cmd_child->herdoc->herdoc_pipe);
//             close(cmd_child->herdoc->herdoc_pipe);
//         }
//     }
//     //RIGHT CHILD COMMAND:
//     if (pcmd->right->type == PIPE)
//     {
//         pcmd_right = (t_pipe  *)pcmd->right;
//         pcmd_right->pipe_fd = p[0];
//         close(p[1]);
//         status = new_exec(pcmd->right, PIPE);
//         status = WEXITSTATUS(status);
//         // exit(status);
//     }
//     else
//     {
//         pid2 = fork();
//         if(pid2 == 0)
//         {
//             cmd_child = (t_cmd_exec  *)pcmd->right;
//             // else
//             // {
//                 if (pcmd->pipe_fd != - 1)
//                     close(pcmd->pipe_fd);
//                 cmd_child->fd_in = p[0];
//                 close(p[1]);
//                 new_exec(pcmd->right, PIPE);
//                 if (cmd_child->herdoc->herdoc_pipe > 0)
//                 {
//                     printf("%d\n",cmd_child->herdoc->herdoc_pipe);
//                     close(cmd_child->herdoc->herdoc_pipe);
//                 }
//             // }
//         }
//     }
//     close(p[0]);
//     close(p[1]);
//     wait(0);
//     waitpid(pid2, &status, 0);
//     return (status);
// }

/********************************************************/
/***************************************************** */
// THE RECURSIVE THAT WORKS FOR NOW !
// THE PIPE WAS PARSED IN A WHILE LOOP (SO THE LAST PIPE IS THE ROOT)
/****************************************************** */

// int recursion_pipe(t_cmd *cmd, int fd)
// {
//     t_pipe  *pcmd;
//     t_cmd_exec  *lchild;
//     t_cmd_exec  *rchild;
//     t_sub_sh  *srchild;
//     t_sub_sh  *slchild;

//     int p[2];
//     int rpid, lpid, status;

//     pipe(p);
//     pcmd = (t_pipe  *)cmd;
//     status = 0;

//     (void)srchild;
//     // LEFT CHILD
//     if (pcmd->left->type == NEW_CMD || pcmd->left->type == SUB_SH)
//     {
//         lchild = (t_cmd_exec  *)pcmd->left;
//         slchild = (t_sub_sh  *)pcmd->left;
//         lpid = fork();
//         if (lpid == -1)
//             return (-1); // Error handling
//         if (lpid == 0)
//         {
//             // Left child process
//             if (pcmd->left->type == SUB_SH )
//                 slchild->fd_out = p[1];           
	// if (pcmd->left->type = = NEW_CMD )
//             else
//                 lchild->fd_out = p[1];
//             // else if (pcmd->left->type == SUB_SH )
//                 // slchild->fd_out = p[1];
//             close(p[0]); // Close read end
//             status = new_exec(pcmd->left, PIPE);
//             exit(status);
//         }
//        // Parent closes write end
//     }
//     else if (pcmd->left->type == PIPE)
//     {
//         recursion_pipe(pcmd->left, p[1]);
//     }
//     close(p[1]);
//     // RIGHT CHILD
//     rchild = (t_cmd_exec  *)pcmd->right;
//     srchild = (t_sub_sh  *)pcmd->right;
//     rpid = fork();
//     if (rpid == -1)
//         return (-1); // Error handling
//     if (rpid == 0)
//     {
//         // Right child process
//         if (fd > 0)
//         {
//             if (pcmd->right->type == SUB_SH)
//                 srchild->fd_out = fd;
//             else
//                 rchild->fd_out = fd;

//         }
//         if (pcmd->right->type == SUB_SH)
//             srchild->fd_in = p[0];
//         else
//             rchild->fd_in = p[0];
//         close(p[1]); // Close write end
//         // status = exec_new_cmd(pcmd->right);
//         status = new_exec(pcmd->right, PIPE);
//         exit(status);
//     }
//     close(p[0]);
//     close (p[1]);
//      // Parent closes read end

//     // Wait for both children
//     waitpid(lpid, &status, 0);
//     waitpid(rpid, &status, 0);
//     status = WEXITSTATUS(status);
//     return (status);
// }
