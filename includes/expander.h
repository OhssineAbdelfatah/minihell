#ifndef EXPANDER_H
#define EXPANDER_H

typedef struct s_node {
    char *str;
    char type;
    struct s_node *next;
} t_node;

char *tokenizer(char *arg);
t_node *splitArg(char *str);
char *joiner(char *arg, t_env* env);
char **expnader(char **argv, t_env *env);

t_node *create_node(char *value, char type);
void add_node(t_node **head, t_node **tail, t_node *node);
char *splitWordVar(char *value, t_env *env);
void mini_expander(t_node **head, t_env *env);
char *expand(t_node **head, t_env *env);

char *ft_name(char *arg);
void free_lst(t_node *head);
char *clean_qts(char *str);

#endif