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



struct		s_my
{
	int		i;
	int		j;
	int		x;
	int		s2len;
	int		s1len;
	char	*res;
};

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


#endif