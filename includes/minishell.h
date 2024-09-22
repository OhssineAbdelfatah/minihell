# ifndef MINISHELL_H
#define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
#include <fcntl.h>
#include <signal.h>

#include "helper.h"
#include "struct.h"
#include "builtins.h"
#include "../libft/libft.h"

/*Testing a new split shit */
int count_tokens_new(char *s);
///////that's it ///

int skip_spaces(char *s, int x);
void exec_cmd(char **tokens, char **env);
void panic(char *str);
int ft_strlen1(char *s);
char **split_shit(char *s);
char *getEnvValue(t_env *env, char *key);
// void exec(t_cmd *cmd);



// debug
void pexit(char *s);



# endif
