/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:17:50 by ilaasri           #+#    #+#             */
/*   Updated: 2024/10/29 14:17:54 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NORM_STRUCTS_H
# define NORM_STRUCTS_H

typedef struct s_without_quotes t_without_quotes;
typedef struct s_parse_sub t_parse_sub;
typedef struct s_parse_new_exec t_parse_new_exec;
typedef struct s_cmd_line t_cmd_line;
typedef struct s_get_herdoc t_get_herdoc;
typedef struct s_herdoc_treat t_herdoc_treat;
typedef struct s_check_tok_sub t_check_sub_tok;
typedef struct s_count_pipe_red t_count_pipe_red;
typedef struct s_count_sub_sh t_count_sub_sh;
typedef struct s_ct_tk_pro t_ct_tk_pro;

struct s_without_quotes
{
    char	*res;
	int res_len;
    int i;
    int j;
    int end;
};

struct s_parse_sub
{
    t_red		*redirect;
	t_herdoc	*herdoc;
	t_cmd		*res;
	t_cmd		*sub_root;
	int			end_sub;
	int			x;
};

struct s_parse_new_exec
{
    t_cmd		*res;
	t_red		*redirect;
	t_herdoc	*herdoc;
	char		*argv;
	char		**argv1;
	int			x;
};

struct s_cmd_line
{
	t_typenode	ref;
	char		*cmd;
	int			i;
	int			j;
};

struct s_get_herdoc
{
	t_del	*str;
	int		ref;
	char	*delimiter;
	int		status;
};

struct s_herdoc_treat
{
	int		p[2];
	char	*str;
	int		pid;
	int		status;
};

struct s_check_tok_sub
{
	int	ref;
	int	i;
	int	which;
	int ret;
};

struct s_count_pipe_red
{
	int i;
	int res;
};

struct s_count_sub_sh
{
	int	i;
	int res;
	int next_par;
};

struct s_ct_tk_pro
{
	int res;
	int i;
	int ref;
	int tmp;
};

#endif