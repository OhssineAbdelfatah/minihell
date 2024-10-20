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

char *joiner(char *arg, t_env* env)
{
    char* new;
    char* tmp_new;
    t_node  *head;
    t_node  *tmp;

    if(ft_strchr(arg, '$') == NULL)
        return arg;
    head = splitArg(arg);
    mini_expander(&head, env);
    tmp = head;
    new = ft_strdup("");
    while(tmp)
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

char **expander(char **argv, t_env *env)
{
    int i ;

    i = -1 ;
    if(!argv || !(*argv))
        return NULL;
    while(argv[++i]){
        // printf("argalloc [%p]\n",argv[i]);
        argv[i] = joiner(argv[i], env);
    }
    return argv;
}