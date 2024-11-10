/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:34:56 by aohssine          #+#    #+#             */
/*   Updated: 2024/11/10 16:34:45 by aohssine         ###   ########.fr       */
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

int	export(t_env **ennv, char **cmd)
{
	int		status;
	t_env	*tmp;
	char	*key;
	char	*value;
	int		i;

	status = 0;
	if (ft_strslen(cmd) == 1){

		if( ennv	&& *ennv )
			printf("aloalo%s\n", cmd[0]);
		return (print_export(ennv), status);
	}
	i = 0;
	while (cmd[++i])
	{
		key = get_key(cmd[i]);
		if (key && is_valid(key))
		{
			tmp = env_exist(key, *ennv);
			value = get_value(cmd[i]);
			if (tmp)
			{
				update_env(tmp, value);
				free(key);
			}
			else
			{
				tmp = creat_new_env(key, ft_strdup(value));
				add_back_env(ennv, tmp);
				free(value);
			}
		}
		else if (!is_valid(key))
		{
			status = 1;
			printf("minishell: export: `%s': not a valid identifier\n", cmd[i]);
			free(key);
		}
	}
	return (status);
}
