#include "../../includes/minishell.h"

void	update_env(t_env *node, char *value)
{
	free(node->value);
	node->value = value;
	return ;
}

void	print_export(t_env **env)
{
	while (env && (*env) != NULL)
	{
		printf("declare -x %s=\"", (*env)->key);
		if ((*env)->value)
			printf("%s", (*env)->value);
		printf("\"\n");
		(*env) = (*env)->next;
	}
}

char	*get_key(char *arg)
{
	char	*eql;

	eql = ft_strchr(arg, '=');
	if (!eql)
		return (ft_strdup(arg));
	eql = ft_strndup(arg, eql - arg);
	return (eql);
}

char	*get_value(char *arg)
{
	char	*eql;

	eql = ft_strchr(arg, '=');
	if (!eql)
		return (NULL);
	eql = ft_strdup(eql + 1);
	return (eql);
}
