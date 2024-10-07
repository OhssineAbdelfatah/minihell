#ifndef HELPER_H
# define HELPER_H

#include "struct.h"



//PARSE THINGS :
/********************************************/

int is_special(char s);
int get_next_quote(char *s,int i);
char **fr9_trb7(char *s);


int dstr_len(char **s);
int _check_tokens(char **tokens);


/****************************************** */

//PARSING SUB SHELL:

/********************************************/

int check_tok_sub(char **tokens);

/****************************************** */

//TOOLS ABT WHITE SPACES
/***************************** */

int is_white(int c);
int is_white_str(char *s);
int is_full_white_str(char *s);

/****************************** */


// char *cmd_line(char **tokens);


//CONSTRACTORS :
/***************************************************/

t_cmd *init_sub(t_cmd *root_sub, t_env *myenv, t_red *redirect, t_herdoc *herdoc);
t_cmd *init_or(t_cmd *left, t_cmd *right);
t_cmd *init_and(t_cmd *left, t_cmd *right);
t_cmd *init_pipe(t_cmd *left, t_cmd *right);
// t_cmd *init_exec(int tp, char *s, char **env);
t_cmd *init_new_cmd(char **argv, t_env *myenv,t_red *redirect, t_herdoc *herdoc);

/****************************************************/

//CONSTRACTORS TOOLS:
/***********************************************/
// void herdoc_content(t_cmd *herd);
t_cmd *init_redire(t_cmd *cmd, char *file , int mode, int fd);
t_cmd *init_herdoc(t_cmd *cmd, char *deliminater);
t_red *get_red(char **tokens, int i,  t_herdoc *herdoc);
t_red *get_red_for_sub(char **tokens, int i);
t_red *creat_red_lst(char **tokens, int i);


/***********************************************/




int get_next_parenties_d(char **s, int i);

char **tokens(char *str);
int _check_str(char *s);
int check_qoutes(char *s);
t_cmd *root(char **tokens, t_env **env);

void print_tree(t_cmd *res);
// void print_tree(t_cmd *res, int level);
int which_one(char *s);
// int skip_nonspaces(char *str, int i);
//  char *ft_substr(char *str, int start, int end)


//new  MODIFICATION :
int get_type(char **tokens, int i);
int get_mode(char **tokens, int i);
// t_red *get_red(char **tokens, int i);
// t_red *get_red(char **tokens, int i, int *herdoc_pipe);
char *cmd_line(char **tokens, int *x);
// t_cmd *init_new_cmd(char *argv, char **env, t_red *redirect);
// t_cmd *init_new_cmd(char **argv, t_env *myenv,t_red *redirect, int herdoc_pipe);
<<<<<<< HEAD
t_cmd *init_new_cmd(char **argv, t_env **myenv,t_red *redirect, t_herdoc *herdoc);
void add_to_lst(t_red *red_lst, char **tokens, int i);
t_red *creat_red_lst(char **tokens, int i);
t_cmd *parse_new_exec(char **tokens, int *i, t_env **myenv);
=======
void add_to_lst(t_red *red_lst, char **tokens, int i);
>>>>>>> 12d9d7a93e8fc6b7ccb1559de06940f29cf3d9ff

//PARSE AST NODES:
/********************************************************** */
t_cmd *root(char **tokens, t_env *env);
t_cmd *parse_new_exec(char **tokens, int *i, t_env *myenv);
t_cmd *parse_pipe_loop(char **tokens, int *i, t_env *myenv);
t_cmd *parse_and_or(char **tokens, int *i, t_env *myenv);
struct cmd *parse_pipe_rec(char **tokens, int *i, t_env *myenv);
t_cmd *parse_sub(char **tokens, int *i,t_env *myenv);
/************************************************************** */

//new EXEC
/************************************ */

int exec_or(t_cmd *cmd);
int exec_and(t_cmd *cmd);
int new_exec(t_cmd *cmd, int ref);
// int new_exec(t_cmd *cmd);
int execute_pipe (t_cmd *cmd);
int recursion_pipe(t_cmd *cmd, int fd);
int exec_new_cmd(t_cmd *cmd);
/************************************ */

//SIGNALS
/************************************** */
void do_nothing(int signal);
void	signal_handler(int signal);
/**************************************** */


//HERDOC 
/*************************************************** */
int get_herdoc(char **tokens,int i, t_herdoc *herdoc);
t_del *first_del(t_del *node, char *value);
t_del *add(t_del *node, char *value);
void print_del(t_del *head);
/****************************************************** */



//ALWAYS FREE
/********************************** */

void free_delimiters(t_del *head);
void free_tree2(t_cmd *cmd);
void free_mynigga(char **str);
void free_tree(t_cmd *cmd);

/************************************* */

//ERROR
/****************** */
void error(char *s, int er_num);
/************************ */
# endif