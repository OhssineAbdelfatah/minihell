# ifndef STRUCT_H
#define STRUCT_H


typedef struct cmd t_cmd;
typedef struct new_cmd t_cmd_exec;
typedef struct token t_token;
typedef struct new_red t_red;
typedef struct s_env_var t_env;
typedef struct s_delimiter t_del;
typedef struct s_herdoc_info t_herdoc;
typedef struct pipe t_pipe;
typedef struct and t_and;
typedef struct or t_or;
typedef struct new_cmd t_new_cmd;
typedef struct sub_sh t_sub_sh;
typedef struct s_dir_cont t_dir_cont;
typedef struct s_globing t_globing ;



struct		s_my
{
	int		i;
	int		j;
	int		x;
	int		s2len;
	int		s1len;
	char	*res;
};

typedef enum s_pos
{
    FIRST,
    MIDLLE,
    LAST,
    ALL
}t_pos;


typedef enum s_in_out
{
    IN,
    OUT
}t_in_out;

typedef enum file
{
    NADA,
    RFILE,
    DIREC,
    ALL_KINDS
}file;

typedef enum ss
{
    NONE,
    SINGLE,
    DOUBLE
}ss;

typedef enum error
{
    PIPE_ER,
    RED_ER,
    AND_ER,
    OR_ER,
    SYNTAX,
    CMD_NOT_F
}t_error;

typedef enum typenode
{
    NEW_CMD,
    EXEC,
    PIPE,
    RED,
    HERDOC,
    AND,
    OR,
    SUB_SH,
    S_SUB,
    END_SUB,
    ENV_VAR,
    FILE_NAME,
    NOTHING,
    STRING,
    SPACES,
    SPECIAL
} t_typenode;

// AST NODES :
/********************* */
struct cmd
{
    int type;
};

struct new_cmd
{
    int type;
    char **argv;
    int fd_in;
    int std_in;
    int fd_out;
    int std_out;
    int last_pipe_cmd;
    t_herdoc *herdoc;
    t_env **myenv;
    t_red *redirect;
};

struct pipe
{
    int type;
    int pipe_fd;
    t_cmd *left;
    t_cmd *right;
};

struct and
{
    int type;
    int status;
    t_cmd *left;
    t_cmd *right;
};

struct or
{
    int type;
    int status;
    t_cmd *left;
    t_cmd *right;
};


struct sub_sh
{
    int type;
    int status;
    int fd_in;
    int fd_out;
    int last_pipe_cmd;
    t_herdoc *herdoc;
    t_env **myenv;
    t_red *redirect;
    t_cmd *sub_root;
};

/*********************************/

struct new_red
{
    int type;
    int mode;
    int fd;
    char *file;
    t_red *next;
};


struct s_env_var {
    char *key;
    char *value;
    t_env *next;
};

typedef struct tfar9
{
    int i;
    int reslen;
    char **res;
    int start;
    int end;
}t_tfar9;

struct s_herdoc_info
{
    int herdoc_pipe;
    int to_exp;
    // t_env **env;
};

struct s_delimiter
{
    char *del;
    int to_exp;
    t_del *next;
};

/******************************** */
//IN ORDER TO EXEC A PIPE PROPERLY !
/********************************* */

typedef struct s_exec_pipe
{
    int status;
    int rpid;
    int lpid;
    int p[2];
    t_pipe *node_p;
    t_cmd_exec *lchild;
    t_cmd_exec *rchild;

} t_execp;


/********************************* */
// WILDCARD THINGS
/********************************* */

typedef struct s_wild
{
    int			i;
	int			j;
	int			pos;
	int			slen;
	t_globing	*ret;
	char		*val;
}t_wild;

typedef struct s_wild_expand
{
    char		**new;
	int			new_len;
	char		*work_dir;
	char		**dir_cont_array;
	t_dir_cont	*dir_cont;
	int			i;
}t_wild_expand;

typedef struct s_new_args
{
    int		i;
	int		j;
	int		tmp;
	char	**new;
}t_new_args;

struct s_dir_cont
{
    char *value;
    char *working_direc;
    int type;
    int valid;
    int hidden;
    t_dir_cont *next;
};

struct s_globing
{
    char *value;
    int found_it;
    int pos;
    t_globing *next;
};

typedef struct s_dir_cont_array
{
	DIR				*dir;
	char			**ret;
	int				retlen;
	struct dirent	*po;
	int				i;
}t_dir_cont_array;


#endif