#include"../../includes/minishell.h"

// void add_back_node(char *line, t_node **head){
//     t_node *tail;
//     t_node *node;

//     tail = NULL;
//     node = create_node(line,' ');
//     add_node(head, &tail, node);
// }

int herdoc_newfd( int fd, t_env* myenv)
{ 
    char *line ;
    int fd_pipe[2];

    pipe(fd_pipe);
    line = get_next_line(fd);
    while(line)
    {
        line = splitWordVar(line, myenv, 0);
        if(line != NULL)
            ft_putstr_fd(line, fd_pipe[1]);
        else
            ft_putstr_fd("\n", fd_pipe[1]);
        line = get_next_line(fd);
    }   
    line = get_next_line(-1);
    close(fd_pipe[1]);
    close(fd);
    return fd_pipe[0];
}

// int expand_herdoc(int fd_herdoc, t_env *myenv)
// {
//     t_node * head;
//     t_node * tmp;
//     int new_fd;

//     head = herdoc_newfd(fd_herdoc);
//     tmp = head;
//     while(tmp)
//     {
//         tmp->str = splitWordVar(tmp->str, myenv); 
//         tmp = tmp->next;
//     }
//     new_fd = 0;
//     return new_fd;
// }