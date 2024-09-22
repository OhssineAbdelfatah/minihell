#include"../../includes/minishell.h"

// minishell> exit a b c d => should exit and print err "{1st arg} :numeric argument required"  1
// minishell> exit 1 b c d => should not exit and print err "exit: too many arguments"  1 
// minishell> exit c => should exit and print err "{1st arg} :numeric argument required"  255

// exit exitvalue
    // exit => exit with last executed cmd
    // exit value => exit with the value specified
    // exit a => print "exit: a: numeric argument required" and exit with a status of 255.
    // exit 1 2 3 => The shell will print an error message similar to "exit: too many arguments" and not exit.

// void exit_blt(char *arg)
// {
//     // get args 
//     // check whether is int // throw error "arg : numeric argument required"
//     // check how many args // the=row error "exit: too many arguments"
//     // no arg // exit status of last cmd
//     // arg valid (one arg and numeric) exit with value
//     char **args;
//     int args_len;
//     args = ft_split(arg, ' ');
//     args_len = ft_strslen(args);
//     if(ft_isdigit(ft_) && args_len > 0){
//         perror("exit :");
//         exit();
//     }
// }


