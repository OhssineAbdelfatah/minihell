#include "../../includes/minishell.h"

int	get_type(char **tokens, int i)
{
	if (ft_strcmp(tokens[i], "<<"))
		return (HERDOC);
	return (RED);
}

int	get_mode(char **tokens, int i)
{
	if (ft_strcmp(tokens[i], "<"))
		return (4);
	if (ft_strcmp(tokens[i], ">>"))
		return (77);
	if (ft_strcmp(tokens[i], ">"))
		return (7);
	return (0);
}

void	assign_her_exp(t_del *lst, t_herdoc *herdoc)
{
	t_del	*tmp;

	tmp = lst;
	if (!tmp)
		return ;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	herdoc->to_exp = tmp->to_exp;
}
