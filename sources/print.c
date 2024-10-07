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


void print_red(t_red *tmp)
{
    // t_red *tmp =  p->redirect; 
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
    struct and *p3;
    struct or *p4;
    struct sub_sh *p5;
    int i = 0;

    if (NULL == res)
        return ;
    if (res->type == NEW_CMD)
    {
        p1 = (struct new_cmd*)res;
        if (p1->argv == NULL)
            printf("'NULL'");
        else
        {
            while (p1->argv[i])
                printf(" %s", p1->argv[i++]);
        }
        if (NULL != p1->redirect)
            print_red(p1->redirect);
        // if (NULL != p1->herdoc)
        //     printf("  d_p:%d",p1->herdoc->herdoc_pipe);
        // printf("");
    }
    else if (res->type == PIPE)
    {
        p2 = (struct pipe *)res;
        printf("[");
        print_tree(p2->left);
        printf(" |");
        print_tree(p2->right);
        printf("]");
    }
    else if (res->type == AND)
    {
        p3 = (struct and *)res;
        printf("[");
        print_tree(p3->left);
        printf(" &&");
        print_tree(p3->right);
        printf("]");
    }
    else if (res->type == OR)
    {
        p4 = (struct or *)res;
        printf("[");
        print_tree(p4->left);
        printf(" ||");
        print_tree(p4->right);
        printf("]");
    }
    else if (res->type == SUB_SH)
    {
        p5 = (struct sub_sh *)res;
        printf("(");
        // print_tree(p4->left);
        // printf("SUB");
        print_tree(p5->sub_root);
        printf(")");
        if (NULL != p5->redirect)
            print_red(p5->redirect);
    }
}

