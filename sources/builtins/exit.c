#include"../../includes/minishell.h"

int ft_isnumber(char *arg)
{
    int i ;

    i = -1;
    if(arg[0] == '-' || arg[0] == '+'){
        i++;
        if(arg[++i] == '\0')
        return 0;
    }
    
    while(arg[++i])
    {
        if(!ft_isdigit(arg[i]))
            return 0;
    }
    return 1;
}

static int	space_sign(const char *s, int *sign)
{
	int	i;

	i = 0;
	while (s[i] && (s[i] == 32 || (s[i] < 14 && s[i] > 8)))
		i++;
	if (s[i] && (s[i] == '-' || s[i] == '+'))
	{
		if (s[i] == '-')
			*sign *= (-1);
		i++;
	}
	return (i);
}

size_t ft_atoi_exit(const char *str)
{
	int					i;
	int					sign;
	size_t	result;
	size_t	temp;

    (void)temp;
	result = 0;
	sign = 1;
	i = space_sign(str, &sign);
	while (str[i] <= '9' && str[i] >= '0')
	{
        temp = result;
		result = result * 10 + str[i] - 48;
        if( (temp != result / 10 && sign == -1) || (temp != result / 10 && sign == 1))
        {
            printf("bash: exit: %s: numeric argument required\n",str);
            exit(255);
        }
		i++;
	}
	return (result * (size_t)sign);
}

int exit_blt(t_new_cmd *cmd)
{
    int args_len;
    size_t status = 0;
    args_len = ft_strslen(cmd->argv);
    printf("exit\n");
    if( args_len == 2)
    {
        if(ft_isnumber(cmd->argv[1])){
            status = ft_atoi_exit(cmd->argv[1]);
            free_mynigga(cmd->argv);
            exit( (unsigned char )status);
        }else{
            error_exit(cmd->argv[1]);
            free_mynigga(cmd->argv);
            exit(255) ;
        }
    }else if( args_len > 2)
    {
        if(ft_isnumber(cmd->argv[1])){
            ft_putstr_fd("bash: exit: too many arguments\n", 2);
            return 1;
        }else
        {
            error_exit(cmd->argv[1]);
            free_mynigga(cmd->argv);
            exit(255);
        }
    }
    free_mynigga(cmd->argv);
    exit(0);
}
