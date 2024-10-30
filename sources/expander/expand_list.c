#include"../../includes/minishell.h"

static int	count_word(char const *s, char c)
{
	size_t	i;
	size_t	words;

	words = 0;
	i = 0;
	if (!s || *s == '\0')
		return (0);
	while (*(s + i) == c)
		i++;
	while (*(s + i))
	{
		if (*(s + i) == c && *(s + i + 1) != c)
			words++;
		i++;
	}
	if (*(s + i - 1) != c)
		words++;
	return (words);
}

t_node *create_node(char *value, char type)
{
    t_node *node = debug_malloc(sizeof(t_node));
    node->str = value;
    node->type = type;
    node->next = NULL;
    return node;
}

void add_node(t_node **head, t_node **tail, t_node *node)
{
    if (*head == NULL) {
        *head = node;
    } else {
        (*tail)->next = node;
    }
    *tail = node;
}

void split_inside_arg(t_node **head)
{
    t_node *tmp;
    t_node *head2;
    t_node *tail;
    char **args;
    int i ;
    tail = NULL;
    head2 = NULL;
    args = ft_split((*head)->str ,' ' );
    i = -1;
    while(args[++i])
    {
        tmp = create_node(ft_strdup(args[i]), 'w');
        add_node(&head2 ,&tail, tmp);
    }
    free_lst(*head);
    *head = head2 ;
}

void mini_expander(t_node **head, t_env *env, int *st)
{
    t_node *tmp;
    char *tmpstr;

    tmp = *head ;
    while(tmp){
        // delete single or double
        if(tmp->type == 'w' || tmp->type == 'd'){
            tmpstr = tmp->str;   
            tmp->str =  splitWordVar(tmp->str, env, st);
            if(tmpstr != tmp->str)
                free(tmpstr);
        }
        tmp = tmp->next;
    }
    tmp = *head ;
    if( !tmp->next && tmp->type == 'w' && tmp->str && count_word(tmp->str, ' ') > 1){
        puts("dkhel itsplita \n");
        split_inside_arg(head);
    }
    return ;
}

//char *dt.start; // start
//char *dt.token; // token
char *splitWordVar(char *value, t_env *env ,int *st)
{
    t_split_arg dt;

    dt.head = NULL;
    while(value){
        dt.start = ft_strchr(value, '$'); 
        if(dt.start && *(dt.start+1)){

            dt.token = ft_strndup(value, dt.start - value);
            dt.node = create_node(dt.token, '0');
            add_node( &dt.head, &dt.tail, dt.node);
            dt.token = ft_strndup(dt.start  , ft_name(dt.start ) - dt.start );
            if(ft_strlen(dt.token) == 1 && *dt.token == '$')
                dt.node = create_node(dt.token, '0');
            else
                dt.node = create_node(dt.token, '1');
            add_node( &dt.head, &dt.tail, dt.node);
            value = ft_name(dt.start) ;
        }
        else{
            dt.node = create_node(ft_strdup(value), '0');
            add_node( &dt.head, &dt.tail, dt.node);
            break;     
        }
    }
    return expand(&dt.head, env, st);
}

char *expand(t_node **head, t_env *env, int *st)
{
    t_expn dt;
    dt.tmp = *head;
    while (dt.tmp)
    {
        if (dt.tmp->type == '1')
        {
            dt.value = getEnvValue(env, dt.tmp->str + 1);
            if(ft_strcmp(dt.tmp->str + 1, "?")){
                free( dt.value);
                dt.value = ft_itoa(*st); // 
            }
            dt.tmpstr = dt.tmp->str;
            dt.tmp->str = ft_strdup(dt.value);
            free(dt.tmpstr);
        }
        dt.tmp = dt.tmp->next;
    }
    dt.tmp = *head;
    dt.new = ft_strdup("");
    while (dt.tmp)
    {
        dt.tmpstr = dt.new ;
        dt.new = ft_strjoin(dt.new, dt.tmp->str);
        free(dt.tmpstr);
        dt.tmp = dt.tmp->next;
    }
    return (free_lst(*head), dt.new);
}