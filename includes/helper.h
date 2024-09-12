#ifndef HELPER_H
# define HELPER_H

#include "struct.h"

int is_white(int c);
int is_white_str(char *s);
int is_special(char s);
int get_next_quote(char *s,int i);

// char *cmd_line(char **tokens);
char **fr9_trb7(char *s);

void free_mynigga(char **str);
void free_tree(t_cmd *cmd);

void herdoc_content(t_cmd *herd);
int dstr_len(char **s);
int _check_tokens(char **tokens);

struct cmd *init_pipe(t_cmd *left, t_cmd *right);
struct cmd *init_exec(int tp, char *s, char **env);
struct cmd *init_redire(t_cmd *cmd, char *file , int mode, int fd);
t_cmd *init_herdoc(t_cmd *cmd, char *deliminater);
char **tokens(char *str);
int _check_str(char *s);
int check_qoutes(char *s);
t_cmd *root(char **tokens, t_env *env);
void print_tree(t_cmd *res);
int which_one(char *s);
// int skip_nonspaces(char *str, int i);
//  char *ft_substr(char *str, int start, int end)


//new  MODIFICATION :
void free_tree2(t_cmd *cmd);
int get_type(char **tokens, int i);
int get_mode(char **tokens, int i);
t_red *get_red(char **tokens, int i);
char *cmd_line(char **tokens, int *x);
// t_cmd *init_new_cmd(char *argv, char **env, t_red *redirect);
t_cmd *init_new_cmd(char *argv, t_env *myenv,t_red *redirect);
void add_to_lst(t_red *red_lst, char **tokens, int i);
t_red *creat_red_lst(char **tokens, int i);
t_cmd *parse_new_exec(char **tokens, int *i, t_env *myenv);


//new EXEC

int new_exec(t_cmd *cmd);
void execute_pipe (t_cmd *cmd);

# endif