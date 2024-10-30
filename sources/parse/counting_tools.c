#include "../../includes/minishell.h"

int	total_sub(char *s)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
			i = get_next_quote(s, i);
		if (s[i] == 40 || s[i] == 41)
			res++;
		i++;
	}
	return (res);
}

int	get_next_parenties(char *s, int i)
{
	int	ref;

	ref = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
			i = get_next_quote(s, i);
		if (s[i] == ')' && ref == 0)
			return (i);
		else if (s[i] == ')' && ref != 0)
			ref--;
		i++;
		if (s[i] == '(')
			ref++;
	}
	error(NULL, 40);
	return (-1);
}
