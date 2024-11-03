#include "../../includes/minishell.h"

void	error(char *s, int er_num)
{
	if (er_num == 40)
		ft_putstr_fd("minishell: syntax error near unexpected token '('\n", 2);
	else if (er_num == 41)
		ft_putstr_fd("minishell: syntax error near unexpected token ')'\n", 2);
	else if (10 == er_num)
		ft_putstr_fd("Quotes !\n", 2);
	else if (er_num == OR)
		ft_putstr_fd("minishell: syntax error near unexpected token '||'\n", 2);
	else if (er_num == AND)
		ft_putstr_fd("minishell: syntax error near unexpected token `&&'\n", 2);
	else if (-1 == er_num || er_num == PIPE)
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	else if (-2 == er_num || er_num == RED || er_num == HERDOC)
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
			2);
	else if (s)
		ft_putstr_fd(s, 2);
}

void error_exit(char* str)
{
	ft_putstr_fd( "bash: exit: ",2);
	ft_putstr_fd( str,2);
	ft_putstr_fd( ": numeric argument required\n",2);
}