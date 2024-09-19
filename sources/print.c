#include "../includes/minishell.h"


//hadi ghi bach nvisualisiw chejra dyalna a batal 


// void check_mode(struct red *s)
// {
//     if (s)
//     {
//         if (s->mode == 4)
//             printf("<");
//         else if (s->mode == 77 )
//             printf(" >> ");
//         else if (s->mode ==  7)
//             printf(" > ");
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
            printf(" << ");
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
        printf("%s ", p1->argv);
        if (NULL != p1->redirect)
            print_red(p1);
        // printf("");
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


