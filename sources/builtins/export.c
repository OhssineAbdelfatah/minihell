/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:34:56 by aohssine          #+#    #+#             */
/*   Updated: 2024/11/10 17:10:59 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*env_exist(char *key, t_env *node)
{
	while (node != NULL)
	{
		if (ft_strcmp(node->key, key))
			return (node);
		node = node->next;
	}
	return (NULL);
}

t_env	*creat_new_env(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->next = NULL;
	node->key = key;
	node->value = value;
	return (node);
}

// int	export(t_env **ennv, char **cmd)
int	export(t_cmd_exec *p)
{
	int		status;
	t_env	*tmp;
	char	*key;
	char	*value;
	int		i;

	status = 0;
	if (ft_strslen(p->argv) == 1)
		return (print_export(*(p->myenv)), status);
	i = 0;
	while (p->argv[++i])
	{
		key = get_key(p->argv[i]);
		if (key && is_valid(key))
		{
			tmp = env_exist(key, *(p->myenv));
			value = get_value(p->argv[i]);
			if (tmp)
			{
				update_env(tmp, value);
				free(key);
			}
			else
			{
				tmp = creat_new_env(key, ft_strdup(value));
				add_back_env(p->myenv, tmp);
				free(value);
			}
		}
		else if (!is_valid(key))
		{
			status = 1;
			printf("minishell: export: `%s': not a valid identifier\n", p->argv[i]);
			free(key);
		}
	}
	return (status);
}
