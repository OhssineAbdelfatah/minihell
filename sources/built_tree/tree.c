/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:10:13 by ilaasri           #+#    #+#             */
/*   Updated: 2024/10/29 19:10:16 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// PARSE NEW_EXEC
/******************************************** */

t_cmd	*parse_new_exec(char **tokens, int *i, t_env **env)
{
	t_parse_new_exec	var;

	var.res = NULL;
	var.x = *i;
	var.herdoc = (t_herdoc *)malloc(sizeof(*var.herdoc));
	if (!var.herdoc)
		panic("malloc failed\n");
	var.herdoc->herdoc_pipe = -1;
	var.herdoc->to_exp = 0;
	get_herdoc(tokens, var.x, var.herdoc);
	var.argv = cmd_line(tokens, i);
	var.argv1 = fr9_trb7(var.argv);
	free(var.argv);
	var.redirect = get_red(tokens, var.x, var.herdoc);
	var.res = (t_cmd *)init_new_cmd(var.argv1, env, var.redirect, var.herdoc);
	return (var.res);
}

/***************************************************************** */
// PARSE_SUB
/*********************************************************** */

t_cmd	*parse_sub(char **tokens, int *i, t_env **myenv)
{
	t_parse_sub	var;

	var.res = NULL;
	var.x = *i;
	var.herdoc = (t_herdoc *)malloc(sizeof(*var.herdoc));
	if (!var.herdoc)
		panic("malloc failed\n");
	var.end_sub = get_end_sub(tokens, *i);
	var.herdoc->herdoc_pipe = -1;
	var.herdoc->to_exp = 0;
	get_herdoc(tokens, *i, var.herdoc);
	(*i)++;
	var.sub_root = parse_and_or(tokens, i, myenv);
	var.redirect = get_red_for_sub(tokens, var.x);
	*i = var.end_sub;
	var.res = (t_cmd *)init_sub(var.sub_root, myenv, var.redirect, var.herdoc);
	return (var.res);
}

/*********************************************************** */
// PARSE PIPE WITH RECURSION :
/********************************************************* */

t_cmd	*parse_pipe_rec(char **tokens, int *i, t_env **myenv)
{
	t_cmd	*res;
	int		what_next;

	what_next = which_one(tokens[*i]);
	if (tokens[*i] && what_next == S_SUB)
		res = parse_sub(tokens, i, myenv);
	else if (tokens[*i] && (what_next == EXEC || what_next == HERDOC
			|| what_next == RED))
		res = parse_new_exec(tokens, i, myenv);
	if (tokens[*i] && is_pipe(tokens[*i]))
	{
		(*i)++;
		res = (t_cmd *)init_pipe(res, parse_pipe_rec(tokens, i, myenv));
	}
	return (res);
}

/************************************************************************* */
// PARSE AND | OR
/************************************************************************* */

t_cmd	*parse_and_or(char **tokens, int *i, t_env **myenv)
{
	t_cmd	*res;
	int		ref;

	res = parse_pipe_rec(tokens, i, myenv);
	ref = is_and_or(tokens[*i]);
	while (tokens[*i] && ref != -1)
	{
		if (ref == AND)
		{
			(*i)++;
			res = (t_cmd *)init_and(res, parse_pipe_rec(tokens, i, myenv));
		}
		if (ref == OR)
		{
			(*i)++;
			res = (t_cmd *)init_or(res, parse_pipe_rec(tokens, i, myenv));
		}
		ref = is_and_or(tokens[*i]);
	}
	return (res);
}

/*************************************************************************** */

t_cmd	*root(char **tokens, t_env **env)
{
	int		i;
	t_cmd	*res;

	i = 0;
	res = NULL;
	res = parse_and_or(tokens, &i, env);
	return (res);
}

/******************************************************************** */
// PARSE IT WITH WHILE LOOP:
/******************************************************************** */

// t_cmd *parse_pipe_loop(char **tokens, int *i, t_env **myenv)
// {
//     t_cmd *res;
//     int what_next;

//     what_next = which_one(tokens[*i]);
//     if (tokens[*i] && what_next == S_SUB)
//         res = parse_sub(tokens, i, myenv);
//     else if (tokens[*i] && (what_next == EXEC || what_next == HERDOC
//|| what_next == RED))
//         res = parse_new_exec(tokens, i, myenv);
//     while  (tokens[*i] && is_pipe(tokens[*i]))
//     {
//         (*i)++;
//          what_next = which_one(tokens[*i]);
//         if (tokens[*i] &&  what_next == S_SUB)
//             res = (t_cmd *)init_pipe(res, parse_sub(tokens , i, myenv));
//         else if (tokens[*i] && (what_next == EXEC || what_next == HERDOC
//|| what_next == RED))
//             res = (t_cmd *)init_pipe(res, parse_new_exec(tokens , i, myenv));
//     }
//     return (res);
// }

// t_cmd *parse_exec(char **tokens, int *i, char **env)
// {
//     t_cmd *res;
//     struct exec_cmd *p;
//     char *argv;

//     res = NULL;
//     if (RED == which_one(tokens[*i]))
//         return (NULL);
//     argv = ft_strdup(tokens[*i]);
//     p = (struct exec_cmd *)init_exec(EXEC,argv, env);
//     res = (t_cmd *)p;
//     (*i)++;
//     return(res);
// }

// t_cmd *parse_redirect(char **tokens, int *i, char **env)
// {
//     t_cmd *res;
//     int fd;
//     int mode;
//     char *file;

//     res = NULL;
//     fd = 1;
//     // write(1, "al\n", 4);
//     // if (tokens[*i] && (which_one(tokens[*i]) != RED))
//     res = parse_exec(tokens, i, env);
//     while (tokens[*i] && (which_one(tokens[*i]) == RED))
//     {
//         if ( 1 == ft_strcmp(tokens[*i], ">>"))
//             mode = 77;
//         else if (ft_strcmp(tokens[*i], ">"))
//             mode = 7;
//         else if (ft_strcmp(tokens[*i], "<"))
//         {
//             mode = 4;
//             fd = 0;
//         }
//         (*i)++;
//         file = ft_strdup(tokens[*i]);
//         (*i)++;
//         res = init_redire(res, file, mode, fd);
//     }
//     return (res);
// }

// t_cmd	*parse_pipe(char **tokens, int *i, t_env **myenv)
// {
// 	t_cmd	*res;

// 	res = parse_new_exec(tokens, i, myenv);
// 	if (tokens[*i] && is_pipe(tokens[*i]))
// 	{
// 		(*i)++;
// 		res = (t_cmd *)init_pipe(res, parse_pipe(tokens, i, myenv));
// 	}
// 	// printf("cmd is parsed\n");
// 	return (res);
// }

// t_cmd *parse_new_exec(char **tokens, int *i, t_env **env)
// {
//     t_cmd *res;
//     t_red *redirect;
//     t_herdoc *herdoc;
//     char *argv;
//     char **argv1;
//     int x;
//     int heredoc_pipe;

//     res = NULL;
//     x = *i;
//     herdoc = (t_herdoc *)malloc(sizeof (*herdoc));
//     if (!herdoc)
//         panic("malloc failed\n");
//     herdoc->herdoc_pipe = -1;
//     herdoc->to_exp = 0;
//     get_herdoc(tokens, *i, herdoc);
//     argv = cmd_line(tokens, i);
//     argv1 = fr9_trb7(argv);
//     free(argv);
//     redirect = get_red(tokens, x, herdoc);
//     res = (t_cmd *)init_new_cmd(argv1, env, redirect, herdoc);
//     return(res);
// }

// t_cmd *root(char **tokens, t_env **env)
// {
//     int i = 0;
//     t_cmd *res;
//     // t_pipe  *p;
//     // t_cmd_exec  *cmd;

//     res = NULL;
//     res = parse_pipe(tokens, &i, env);
//     // if (res->type == PIPE)
//     // {
//     //     // p = (t_pipe  *)res;
//     //     // cmd = (t_cmd_exec  *)p->right;
//     //     // printf("root heredoc pipe cmd :%d\n", cmd->);
//     //     // printf("root type cmd :%d\n", cmd->type);
//     //     // printf("root left cmd :%s\n", cmd->argv);
//     //     // printf("root cmd :%d\n", p->left->type);
//     //     // printf("root cmd :%d\n", res->type);
//     // }
//     return(res);
// }
