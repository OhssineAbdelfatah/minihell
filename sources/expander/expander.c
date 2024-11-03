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


// char *joiner(char *arg, t_env* env, int *st)
// {
//     char* new;
//     char* tmp_new;
//     t_node  *head;
//     t_node  *tmp;
    
//     head = splitArg(arg);
//     mini_expander(&head, env,st);
//     tmp = head;
//     new = ft_strdup("");
//     while(tmp )
//     {   
//         tmp_new = new;
//         new = ft_strjoin(new, tmp->str);
//         free(tmp_new);
//         tmp = tmp->next ;
//     }
//     free_lst(head);
//     free(arg);
//     return new;
// }



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

char *mini_joiner(t_node *head){
    t_node *tmp;
    char *new;
    char *tmp_new;

    tmp = head;
    new = ft_strdup("");
    while(tmp )
    {   
        tmp_new =new;
        new = ft_strjoin(new, tmp->str);
        free(tmp_new);    
        tmp = tmp->next ;
    }
    free_lst(head);
    return new;
}

int count_arg(char *arg)
{
    char *token;
    size_t	i;
    char c ;
	size_t	words;

    token = tokenizer(arg);
    c = ' ';
	words = 0;
	i = 0;
	if (*arg == '\0')
		return (0);
	while (arg[i] == c && token[i] == 'w' )
		i++;
	while (arg[i])
	{
		if (arg[i] == c && arg[i+1] != c && token[i] == 'w')
			words++;
		i++;
	}
	if (arg[i-1] != c && token[i] != 'w')
		words++;
    free(token);
	return (words);
}

int skip_space_in_word(char *arg, int start)
{
    int i;
    char *token;

    token = tokenizer(arg);
    if( (size_t)start > ft_strlen(arg))
        return (int)ft_strlen(arg);
    i = 0;
    while(arg[i+start])
    {
        if(arg[i+start] == ' ' && token[i+start] == 'w')
            i++;
        else{
            free(token);
            return i+start;
        }
    }
    free(token);
    return i+start;
}

int skip_char(char *arg, int start)
{
    int i;
    char *token;

    token = tokenizer(arg);
    i = 0;
    while(arg[i+start])
    {
        if((arg[i+start] == ' ' && token[i+start] == 'w')){
            free(token);
            return i+start;
        }
        i++;
    }
    free(token);
    return i+start;
}

char **split_arg(char *arg)
{
    char **new_arg;
    int i ;
    int j ;
    int looper;
    int end;

    if(!arg)
        return NULL;
    looper = skip_space_in_word(arg, 0);
    i = count_arg(arg);
    new_arg = malloc((i+1) * sizeof(char *));
    j = -1;
    end = 0;
    while(++j < i){
        end = skip_char(arg, looper +1) +1;
        new_arg[j] = ft_strndup(arg +looper, end -1 - looper);
        looper = skip_space_in_word(arg,end );
    }
    new_arg[j] = NULL;
    return new_arg;
}

void print_argv(char **av)
{
    if( !av || !(*av))
    {
        printf("NULL\n");
        return ;
    }
    while(*av++)
        puts(*av);
    
}

void spliter_args(t_argv *args)
{
    while(args)
    {
        if(args->str && count_arg(args->str) > 1)
        {
            args->str_splited = split_arg(args->str); 
            args->len = ft_strslen(args->str_splited);
        }
        args = args->next;
    }
}


int count_newArgv(t_argv *tmp)
{
    int  i;
    i = 0;
    while (tmp)
    {
        if(tmp->len != 0)
            i += tmp->len ;
        else 
            i++;
        tmp = tmp->next;
    }
    return i;
}

char **join_args(t_argv *args)
{
    int i ;
    int i_subarg ;
    int i_newargv ;
    char **new_argv;

    i = count_newArgv(args);
    new_argv = malloc( (i + 1) * sizeof(char *));
    i_newargv = -1;
    while(args){
        i_subarg = -1;
        if(args->str_splited){
            while(args->str_splited[++i_subarg])
                new_argv[++i_newargv] = ft_strdup(args->str_splited[i_subarg]);
        }
        else 
            new_argv[++i_newargv] = ft_strdup(args->str);
        args = args->next ;
    }
    new_argv[++i_newargv] = NULL;
    return new_argv;
}

char **join_no_split(t_argv *args)
{
    int i;
    char **org_av;
    char *tmp_av;

    org_av = args->orginal;
    i = -1;
    while(args){
        tmp_av =org_av[++i]; 
        org_av[i] = ft_strdup(args->str);
        free(tmp_av);
        args = args->next ;
    }
    org_av[++i] = NULL;
    return org_av;
}

char **joiner(t_argv *args, t_env* env, int *st,int type)
{
    t_argv* tmp;
    char** new;
    char *tmp_str;

    new = NULL;
    tmp = args ;
    while(tmp)
    {
        tmp->arg = splitArg(tmp->str);
        mini_expander(&(tmp->arg), env, st);
        tmp_str =  tmp->str ;
        tmp->str =  mini_joiner(tmp->arg);
        free(tmp_str);
        tmp = tmp->next;
    }
    if(type == HERDOC)
        new = join_no_split(args);
    else if(type == CMD_EXPN | type == RED_EXPN){
        spliter_args(args);
        new = join_args(args);
    }
    return new;
}

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
        node = create_argv(NULL, argv[i], argv);
        add_argv(&head ,&tail ,node);
    }
    free_mynigga(argv);
    return head ;
}

void free_argv_lst(t_argv *head, int type)
{
    t_argv * tmp;

    while(head){
        tmp = head->next;
        if(type == CMD_EXPN || type == RED_EXPN)
            free(head->str);
        free_split(head->str_splited);
        free(head);
        head = tmp;
    }
}


int should_expand(char **argv)
{
    int i;

    i = 0;
    while (argv[i])
    {
        if (ft_strchr(argv[i], '$'))
            return 1;
        i++;
    }
    return 0;
}
char **expander(char **argv, t_env *env, int *st,int type)
{
    char **new_argv;
    t_argv *args;

    if(!argv || !(*argv))
        return NULL;
    if (0 == should_expand(argv))
    {
        // printf("No expand needed !\n");
        return argv;
    }    
    args = argv_to_lst(argv);
    new_argv = joiner(args, env, st,type);
    free_argv_lst(args, type);
    if(type == CMD_EXPN )
        free(argv);
    return new_argv;
}