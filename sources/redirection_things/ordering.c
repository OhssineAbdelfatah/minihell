/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ordering.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 20:28:00 by ilaasri           #+#    #+#             */
/*   Updated: 2024/10/29 20:28:02 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*join_cmd(char *s1, char *s2)
{
	int		i;
	int		reslen;
	char	*res;
	int		l;

	reslen = ft_strlen(s1) + ft_strlen(s2);
	if (NULL != s1)
		reslen += 1;
	res = (char *)malloc(reslen + 1);
	l = ft_strlen(s1);
	i = 0;
	while (i < l)
	{
		res[i] = s1[i];
		i++;
	}
	if (l > 0)
		res[i] = 32;
	i++;
	l = 0;
	while ((size_t)l < ft_strlen(s2))
		res[i++] = s2[l++];
	res[i] = 0;
	free(s1);
	return (res);
}

int	while_breaker(t_cmd_line *var, char **tokens)
{
	if (PIPE == var->j || var->j == OR || var->j == AND || var->j == END_SUB
		|| var->j == S_SUB)
		return (1);
	if (var->ref == RED || var->ref == HERDOC)
		var->ref = FILE_NAME;
	else if (FILE_NAME == var->ref)
		var->ref = EXEC;
	if (var->j == RED || var->j == HERDOC)
		var->ref = var->j;
	if (var->ref == EXEC)
	{
		if (NULL == var->cmd)
			var->cmd = ft_strdup(tokens[var->i]);
		else
			var->cmd = join_cmd(var->cmd, tokens[var->i]);
	}
	return (0);
}

char	*cmd_line(char **tokens, int *x)
{
	t_cmd_line	var;

	var.i = *x;
	var.ref = EXEC;
	var.cmd = NULL;
	while (tokens[var.i])
	{
		var.j = which_one(tokens[var.i]);
		if (while_breaker(&var, tokens))
			break ;
		var.i++;
	}
	*x = var.i;
	return (var.cmd);
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

int	get_type(char **tokens, int i)
{
	if (ft_strcmp(tokens[i], "<<"))
		return (HERDOC);
	return (RED);
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


void child_work(t_herdoc_treat *var, t_del *lst)
{
    
}

void parent_work(t_herdoc_treat *var, t_herdoc *herdoc)
{

}
int	herdoc_treat(t_del *lst, t_herdoc *herdoc)
{
    t_herdoc_treat var;
	int		p[2];
	char	*str;
	int		pid;
	int		status;

	status = 0;
	if (NULL == lst)
		return (0);
	pipe(p);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, NULL);
		while (lst != NULL)
		{
			while (1)
			{
				str = readline(">");
				if (!str)
				{
					error("minishell: here-document delimited by EOF\n", -9);
					break ;
				}
				if (ft_strcmp(str, lst->del))
				{
					free(str);
					break ;
				}
				if (lst->next == NULL)
				{
					ft_putstr_fd(str, p[1]);
					ft_putstr_fd("\n", p[1]);
				}
				free(str);
			}
			lst = lst->next;
		}
		close(p[1]);
		close(p[0]);
		exit(0);
	}
	else if (pid > 0)
	{
		signal(SIGINT, do_nothing);
		waitpid(pid, &status, 0);
		if (WTERMSIG(status) == SIGINT)
		{
			g_sig = 130;
			status = 1;
			printf("CHANGING the status \n");
		}
		else
			status = 0;
		if (g_sig == -1)
			herdoc->herdoc_pipe = p[0];
		else
			close(p[0]);
		close(p[1]);
	}
	return (status);
}

int	while_breaker2(t_get_herdoc *var, char **tokens, int *i)
{
	if (var->ref == END_SUB || var->ref == S_SUB)
		return (1);
	var->ref = which_one(tokens[*i]);
	if (var->ref == HERDOC)
	{
		(*i)++;
		var->delimiter = ft_strdup(tokens[*i]);
		if (NULL == var->str)
			var->str = first_del(var->str, var->delimiter);
		else
			var->str = add(var->str, var->delimiter);
	}
	return (0);
}

int	get_herdoc(char **tokens, int i, t_herdoc *herdoc)
{
	t_get_herdoc	var;

	var.status = 0;
	var.str = NULL;
	var.ref = which_one(tokens[i]);
	while (tokens[i] && PIPE != var.ref && var.ref != AND && var.ref != OR)
	{
		if (while_breaker2(&var, tokens, &i))
			break ;
		i++;
	}
	assign_her_exp(var.str, herdoc);
	if (g_sig == -1)
		var.status = herdoc_treat(var.str, herdoc);
	free_delimiters(var.str);
	return (var.status);
}

t_red	*get_red(char **tokens, int i, t_herdoc *herdoc)
{
	t_red	*red_lst;
	int		ref;

	red_lst = NULL;
	ref = which_one(tokens[i]);
	(void)herdoc;
	while (tokens[i] && PIPE != ref && ref != AND && ref != OR)
	{
		if (ref == END_SUB)
			break ;
		ref = which_one(tokens[i]);
		if (ref == RED || HERDOC == ref)
		{
			if (NULL == red_lst)
				red_lst = creat_red_lst(tokens, i);
			else
				add_to_lst(red_lst, tokens, i);
			if (!red_lst)
				return (NULL);
			i++;
		}
		i++;
	}
	return (red_lst);
}

t_red	*get_red_for_sub(char **tokens, int i)
{
	t_red	*red_lst;
	int		ref;

	red_lst = NULL;
	ref = 0;
	i = get_next_parenties_d(tokens, i) + 1;
	while (tokens[i] && PIPE != ref && ref != AND && ref != OR)
	{
		ref = which_one(tokens[i]);
		if (ref == END_SUB)
			break ;
		if (ref == RED || HERDOC == ref)
		{
			if (NULL == red_lst)
				red_lst = creat_red_lst(tokens, i);
			else
				add_to_lst(red_lst, tokens, i);
			if (!red_lst)
				return (NULL);
			i++;
		}
		i++;
	}
	return (red_lst);
}
