#include "../includes/minishell.h"


//hadi ghi bach nvisualisiw chejra dyalna a batal 



// void check_mode(struct red *s)
// {
//     if (s)
//     {
//         if (s->mode == 4)
//             printf(" < ");
//         else if (s->mode == 77 )
//             printf(" >> ");
//         else if (s->mode ==  7)
//             printf(" > ");
//     }
// }

// void print_tree(t_cmd *res)
// {
//     struct exec_cmd *p1;
//     struct pipe *p2;
//     struct red *p3;
//     struct heredoc *p4;


//     printf("printing begins \n");

//     if (NULL == res)
//         return;
//     if (RED == res->type)
//     {
//         p3 = (struct red*)res;
//         write(1, "(", 1);
//         print_tree(p3->cmd);
//         check_mode(p3);
//         printf("%s)", p3->file);    
//     }
//     else if (res->type == EXEC)
//     {
//         p1 = (struct exec_cmd *)res;
//         write(1, "SEGV\n", 6);
//         // pri
//         // printf("%s",p1->argv);
//         // write(1, "SEGV4\n", 7);
//     }
//     else if (res->type == PIPE)
//     {
//         p2 = (struct pipe *)res;
//         printf("(");
//         print_tree(p2->left);
//         printf("|");
//         print_tree(p2->right);
//         printf(")");
//     }
//     else if (res->type == HERDOC)
//     {
//         p4 = (struct heredoc *)res;
//         printf("(");
//         print_tree(p4->cmd);
//         printf("<<");
//         printf(" %s", p4->delimiter);
//         printf(")");
//     }
//     else
//     {
//         p3 = (struct red *)res;
//         printf("undefined :/ type:%d, file:%s, mode: %d", res->type,p3->file, p3->mode);
//     }
// }



void check_mode(struct red *s)
{
    if (s)
    {
        if (s->mode == 4)
            printf("<");
        else if (s->mode == 77 )
            printf(" >> ");
        else if (s->mode ==  7)
            printf(" > ");
    }
}

// void print_tree(t_cmd *res)
// {
//     struct exec_cmd *p1;
//     struct pipe *p2;
//     struct red *p3;
//     struct heredoc *p4;

//     if (NULL == res)
//         return ;
//     if (res->type == RED)
//     {
//         p3 = (struct red*)res;
//         printf("(");
//         print_tree(p3->cmd);
//         check_mode(p3);
//         printf("file:%s)", p3->file);    
//     }
//     else if (res->type == EXEC)
//     {
//         p1 = (struct exec_cmd *)res;
//         // write(1, "SEGV\n", 6);
//         printf("(cmd :%s)",p1->argv);
//         // write(1, "SEGV4\n", 7);
//     }
//     else if (res->type == PIPE)
//     {
//         p2 = (struct pipe *)res;
//         printf("(");
//         print_tree(p2->left);
//         printf("|");
//         print_tree(p2->right);
//         printf(")");
//     }
//     else if (res->type == HERDOC)
//     {
//         p4 = (struct heredoc *)res;
//         printf("(");
//         print_tree(p4->cmd);
//         printf("<<");
//         printf(" %s", p4->delimiter);
//         printf(")");
//     }
//     else
//     {
//         p3 = (struct red *)res;
//         printf("undefined :/ type:%d, file:%s, mode: %d", res->type,p3->file, p3->mode);
//     }
// }



void print_red(struct new_cmd *p)
{
    t_red *tmp =  p->redirect; 
    while (NULL != tmp)
    {
        if (tmp->mode == 77)
            printf(" >> ");
        if (tmp->mode == 7)
            printf(" > ");
        if (tmp->mode == 4)
            printf(" < ");
        if (tmp->type == HERDOC)
            printf("<<");
        printf("%s", tmp->file);
        tmp = tmp->next;
    }
}

void print_tree(t_cmd *res)
{
    struct new_cmd *p1;
    struct pipe *p2;


    if (NULL == res)
        return ;
    if (res->type == NEW_CMD)
    {
        // print_new_cmd(res);
        p1 = (struct new_cmd*)res;
        printf("( %s ", p1->argv);
        if (NULL != p1->redirect)
            print_red(p1);
        printf(")");
    }
    else if (res->type == PIPE)
    {
        p2 = (struct pipe *)res;
        printf("(");
        print_tree(p2->left);
        printf("|");
        print_tree(p2->right);
        printf(")");
    }
}


