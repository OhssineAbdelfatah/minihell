#include "../includes/minishell.h"
// #include <readline/readline.h>


void do_nothing(int signal)
{
    (void)signal;
    printf("\n");
    return;
}

void	signal_handler(int signal)
{
	(void)signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	sig =1300;
}
