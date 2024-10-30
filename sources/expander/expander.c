#include"../../includes/minishell.h"

/*
    // this sould be applied to each arg char *
    tokenizer
    splitArg
    expander
        splitWordVar
            expand
*/

// char *tokenizer(char *arg)
// {
//     char *tokens = ft_calloc(sizeof(char) * ft_strlen(arg) +1,1);
// 	    bool in_double_quotes = false;
// 	    bool in_single_quotes = false;
// 	    char prevChar = ' ';
	    
// 	    int i = -1;
// 	    while(++i < (int)ft_strlen(arg) +1)
// 	      tokens[i] = '0';
// 	    i = -1;
// 	    while (arg[++i])
// 	    {
// 	        if (arg[i] == '\'' || arg[i] == '\"') {
// 	            if (arg[i] == '\"' && !in_single_quotes) {
// 	                tokens[i] = 'd';
// 	                in_double_quotes = !in_double_quotes;
// 	            } else if (arg[i] == '\'' && !in_double_quotes) {
// 	                tokens[i] = 's';
// 	                in_single_quotes = !in_single_quotes;
// 	            }
// 	        }
// 	        else if(!in_single_quotes && !in_double_quotes 
// 	                    && (prevChar == '\'' || prevChar == '\"' || i == 0)) {
// 	                    tokens[i] = 'w';
// 	        }
// 	        prevChar = arg[i];
// 	        if (in_double_quotes && tokens[i] == '0')
// 	            tokens[i] = 'd';
// 	        else if(in_single_quotes && tokens[i] == '0')
// 	            tokens[i] = 's';
// 	        else if(!in_single_quotes && !in_double_quotes  && tokens[i] == '0')
// 	            tokens[i] = 'w';
// 	    }
// 	    tokens[i] = '\0';
// 	    return tokens;
// }

static t_split_arg init_spliter(t_split_arg data, char *str)
{
    data.head =NULL ;
    data.tail =NULL ;
    data.start = str ;
    data.indx = 0;
    data.token = tokenizer(str);
    data.prevChar = data.token[0];
    return data ;
}

void print_nodes(t_node *head)
{
    
    while(head)
    {
        // printf("str[%s] type[%c]\n",head->str ,head->type);
        head = head->next;
    }
}

t_node *splitArg(char *str)
{
    t_split_arg dt;
    int i ;

    dt = (t_split_arg){0};
    dt = init_spliter(dt, str);
    i = -1;
    while (dt.token[++i])
    {
        if(dt.token[i] != dt.prevChar && i > 0){
            dt.tmpdup = ft_strndup(dt.start , str +i - dt.start );
            dt.node = create_node(dt.tmpdup, dt.prevChar) ;
            add_node(&(dt.head) , &(dt.tail), dt.node);
            dt.start = str+i ;
            dt.indx = i;
        }
        if(dt.token[dt.indx] == dt.token[i] && dt.token[i+1] == '\0'){
            dt.tmpdup = ft_strndup(dt.start , str +i - dt.start +1);
            dt.node = create_node(dt.tmpdup, dt.prevChar) ;
            add_node(&(dt.head) , &(dt.tail), dt.node);
        }
        dt.prevChar = dt.token[i];
    }
    return (free(dt.token), (dt.head));
}

int strlst(t_node *tmp){
    int lst_size;

    lst_size = 0;
    while(tmp)
    {
        lst_size++;
        tmp = tmp->next;
    }
    return lst_size;
}


char *joiner(char *arg, t_env* env, int *st)
{
    char* new;
    char* tmp_new;
    t_node  *head;
    t_node  *tmp;
    
    head = splitArg(arg);
    mini_expander(&head, env,st);
    tmp = head;
    new = ft_strdup("");
    while(tmp )
    {   
        tmp_new = new;
        new = ft_strjoin(new, tmp->str);
        free(tmp_new);
        tmp = tmp->next ;
    }
    free_lst(head);
    free(arg);
    return new;
}



void print_arg(t_argv *head)
{
    while(head)
    {
        printf("arg [%s]\n", head->str);
        while(head->arg){
            printf("%s \t",head->arg->str) ;
            head->arg = head->arg->next ;
        }
        puts("");
        head = head->next ;
    }
}

// char **joiner(t_argv *args, t_env* env, int *st)
// {
//     t_argv* tmp;
//     char** new;

//     tmp = args ;
//     while(tmp)
//     {
//         tmp->arg = splitArg(tmp->str);
//         mini_expander(&(tmp->arg), env,st);
//         tmp = tmp->next;
//     }

//     print_arg(args);
   
//     new = NULL;
//     return new;
// }

// char **expander(char **argv, t_env *env, int *st)
// {
//     int i ;
//     int old_len;

//     old_len = ft_strslen(argv);

//     i = -1 ;
//     if(!argv || !(*argv))
//         return NULL;
//     while(argv[++i])
//         argv[i] = joiner(argv[i], env, st);
//     return argv;
// }

t_argv *argv_to_lst(char **argv)
{
    int i ;
    t_argv *head;
    t_argv *tail;
    t_argv *node;

    tail = NULL ;
    head = NULL ;
    i = -1 ;
    while(argv[++i])
    {
        node = create_argv(NULL, argv[i]);
        add_argv(&head ,&tail ,node);
    }
    return head ;
}

// char **lst_to_argv(){

// }

char **expander(char **argv, t_env *env, int *st)
{
    int i ;
    // char **new_argv;
    // t_argv *args;

    i = -1 ;
    if(!argv || !(*argv))
        return NULL;
    // args = argv_to_lst(argv);
    // return NULL;
    // print_arg(args);
    while(argv[++i])
        argv[i] = joiner(argv[i], env, st);
    return argv;
}