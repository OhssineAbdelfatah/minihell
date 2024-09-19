# ifndef STRUCT_H
#define STRUCT_H


typedef struct cmd t_cmd;
typedef struct token t_token;
typedef struct new_red t_red;
typedef struct s_env_var t_env;



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

typedef enum typenode
{
    EXEC,
    PIPE,
    RED,
    HERDOC,
    ENV_VAR,
    FILE_NAME,
    NOTHING,
    STRING,
    NEW_CMD
} t_typenode;


struct cmd
{
    int type;
};

struct exec_cmd
{
    int type;
    char *argv;
    char **env;
};

struct pipe
{
    int type;
    int pipe_fd;
    t_cmd *left;
    t_cmd *right;
};

struct red
{
    int type;
    int mode;
    int fd;
    char **content;
    char *file;
    int last_red;
    t_cmd *cmd;
};

struct heredoc {
    int type;         
    struct cmd *cmd;  
    char *delimiter;   
    char **content; 
};


struct token
{
    int type;
    char *cont;
    t_token *next;
    t_token *prev;    
};

struct new_red
{
    int type;
    int mode;
    int fd;
    char *file;
    t_red *next;
};

struct new_cmd
{
    int type;
    char *argv;
    char **env;
    int fd_in;
    int fd_out;
    int last_pipe_cmd;
    int herdoc_pipe;
    t_env *myenv;
    t_red *redirect;
};

struct s_env_var {
    char *key;
    char *value;
    bool valid;
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

#endif