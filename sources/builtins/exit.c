#include"../../includes/minishell.h"

// minishell> exit a b c d => should exit and print err "{1st arg} :numeric argument required"  1
// minishell> exit 1 b c d => should not exit and print err "exit: too many arguments"  1 
// minishell> exit c => should exit and print err "{1st arg} :numeric argument required"  255

// exit exitvalue
    // exit => exit with last executed cmd
    // exit value => exit with the value specified
    // exit a => print "exit: a: numeric argument required" and exit with a status of 255.
    // exit 1 2 3 => The shell will print an error message similar to "exit: too many arguments" and not exit.
int ft_isnumber(char *arg)
{
    int i ;

    i = -1;
    if(arg[0] == '-' || arg[0] == '+')
        i++;
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

long long ft_atoi_exit(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	result;
	unsigned long long	temp;

    (void)temp;
	result = 0;
	sign = 1;
	i = space_sign(str, &sign);
	while (str[i] <= '9' && str[i] >= '0')
	{
		temp = result;
		result = result * 10 + str[i] - 48;
		i++;
	}
	return (result * sign);
}

int exit_blt(t_new_cmd *cmd)
{
    int args_len;
    long status = 0;
    args_len = ft_strslen(cmd->argv);
    printf("exit\n");
    if( args_len == 2)
    {
        if(ft_isnumber(cmd->argv[1])){
            status = ft_atoi_exit(cmd->argv[1]);
            printf("%ld \n",status);
            printf("%ld \n",LONG_MAX);
            if(status < LONG_MIN || status > LONG_MAX)
                printf("0bash: exit: %s: numeric argument required\n", cmd->argv[1]);
            exit( (unsigned char )status);
        }else{
            printf("1bash: exit: %s: numeric argument required\n", cmd->argv[1]);
            exit(255) ;
        }

    }else if( args_len > 2)
    {
        if(ft_isnumber(cmd->argv[1])){
            printf("2bash: exit: too many arguments\n");
            return 1;
        }else{
            printf("3bash: exit: too many arguments\n");
            exit(255);
        }
    }
    exit(0);
}



/*
    CASES

    exit 0<n<255
        exit yes
        status n
    
    exit 100000000000000000000000000 (max is )
        exit yes
        bash: exit: 100000000000000000000000000: numeric argument required
        status 255
    
    exit a 1
        exit  yes
        bash: exit: a: numeric argument required
        status 255

    exit 1 a
        exit no
        bash: exit: too many arguments
        status 1

     exit a
        exit yes
        bash: exit: a: numeric argument required
        status 255
*/