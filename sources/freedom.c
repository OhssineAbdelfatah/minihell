#include "../includes/minishell.h"

// void free_cmd(t_cmd *cmd)
// {
//     struct exec_cmd *p;

//     p = (struct exec_cmd *)cmd;
//     free(p->argv);
//     p->argv = NULL;
//     free(p);
//     p = NULL;
// }

// void free_pipe(t_cmd *cmd)
// {
//     struct pipe *p;

//     p = (struct pipe *)cmd;
//     free_tree(p->left);
//     free_tree(p->right);
//     free(p);
//     p = NULL;
// }

// void free_red(t_cmd *cmd)
// {
//     struct red *p;

//     p = (struct red *)cmd;
//     free(p->file);
//     p->file = NULL;
//     free_tree(p->cmd);
//     free(p);
//     p = NULL;
// }


void free_red_lst(t_red **lst)
{
    t_red *tmp;

    tmp = (*lst)->next;
    while (NULL != *lst)
    {
        tmp = (*lst)->next;
        free((*lst)->file);
        // lst->file = NULL;
        // *lst = NULL;
        free(*lst);
        *lst = tmp;
    }
    *lst = NULL;
    // tmp = lst->next;
    // while (tmp)
    // {
    //     tmp = lst->next;
    //     printf("file :%s \n", lst->file);
    //     // free(lst->file);
    //     // printf("file :%s \n", lst->file);
    //     lst->file = NULL;
    //     // lst = NULL;
    //     free(lst);
    //     lst = tmp;
    // }
    // lst = NULL;
}

void free_new_cmd(t_cmd *cmd)
{
    struct new_cmd *p;

    //  write (1, "freeing\n", 9);
    p = (struct new_cmd *)cmd;
    // printf("cmd addr:%p\n", &(*p));
    // printf("cmd argv addr:%p\n", &(*(p->argv)));
    free(p->argv);
    p->argv = NULL;
    if (NULL != p->redirect)
        free_red_lst(& (p->redirect));
    free(p);
}


void free_pipe2(t_cmd *cmd)
{
    struct pipe *p;

    p = (struct pipe *)cmd;
    free_tree2((p->left));
    free_tree2((p->right));
    free(p);
    p = NULL;
}

void free_tree2(t_cmd *cmd)
{
    // printf("cmd TYPE :%d\n", cmd->type);
    if (!cmd)
        return;
    if (cmd->type == NEW_CMD)
    {
        //  write (1, "freeing\n", 9);
        free_new_cmd(cmd);
    }
    else if (cmd->type == PIPE)
        free_pipe2(cmd);
}

// void free_tree(t_cmd *cmd)
// {
//     if (!cmd)
//         return;
//     // if (cmd->type == EXEC)
//     //     free_cmd (cmd);
//     if (cmd->type == NEW_CMD)
//         free_new_cmd(cmd);
//     else if (cmd->type == PIPE)
//         free_pipe(cmd);
//     // else if (cmd->type == RED)
//     //     free_red (cmd);
// }
