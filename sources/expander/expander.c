#include"../../includes/minishell.h"

/*

    // this sould be applied to each arg char *
    tokenizer
    splitArg
    expander
        splitWordVar
            expand

*/
char *tokenizer(char *arg)
{
    char *tokens = ft_calloc(sizeof(char) * ft_strlen(arg) +1,1);
	    bool in_double_quotes = false;
	    bool in_single_quotes = false;
	    char prevChar = ' ';
	    
	    int i = -1;
	    while(++i < (int)ft_strlen(arg) +1)
	      tokens[i] = '0';
	    i = -1;
	    while (arg[++i])
	    {
	        if (arg[i] == '\'' || arg[i] == '\"') {
	            if (arg[i] == '\"' && !in_single_quotes) {
	                tokens[i] = 'd';
	                in_double_quotes = !in_double_quotes;
	            } else if (arg[i] == '\'' && !in_double_quotes) {
	                tokens[i] = 's';
	                in_single_quotes = !in_single_quotes;
	            }
	        }
	        else if(!in_single_quotes && !in_double_quotes 
	                    && (prevChar == '\'' || prevChar == '\"' || i == 0)) {
	                    tokens[i] = 'w';
	        }
	        prevChar = arg[i];
	        if (in_double_quotes && tokens[i] == '0')
	            tokens[i] = 'd';
	        else if(in_single_quotes && tokens[i] == '0')
	            tokens[i] = 's';
	        else if(!in_single_quotes && !in_double_quotes  && tokens[i] == '0')
	            tokens[i] = 'w';
	    }
	    tokens[i] = '\0';
	    return tokens;
}

t_node *splitArg(char *str)
{
    char *token;
    char prevChar;
    t_node *head;
    t_node *tail;
    t_node *node;
    char *start = str;
    int indx = 0;
    int i =-1;
    head = NULL;
    tail = NULL;
    token = tokenizer(str);
    //ALWAYS INITIALIZE YOUR VARIABALS >>
    prevChar = token[0];
    while (token[++i])
    {
        if(token[i] != prevChar && i > 0){
            node = create_node(ft_strndup(start , str +i - start ), prevChar) ;
            add_node(&head , &tail, node);
            start = str+i ;
            indx = i;
        }
        if(token[indx] == token[i] && token[i+1] == '\0'){
            node = create_node(ft_strndup(start , str +i - start +1), prevChar) ;
            add_node(&head , &tail, node);
        }
        prevChar = token[i];
    }
    free(token);
    return head;
}
char *joiner(char *arg, t_env* env)
{
    char* new;
    char* tmp_new;
    t_node  *head;
    t_node  *tmp;

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
    // free list
    // free(nn);
    return new;
}

char **expander(char **argv, t_env *env)
{
    int i ;

    i = -1 ;
    if(!argv || !(*argv))
        return NULL;
    while(argv[++i])
        argv[i] = joiner(argv[i], env);
    return argv;
}