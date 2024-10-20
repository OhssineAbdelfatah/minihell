GNL = lib/gnl/get_next_line.c lib/gnl/get_next_line_utils.c

CFILES = sources/one.c sources/two.c sources/constractors.c sources/parse.c \
            sources/print.c sources/tree.c sources/exec.c sources/exec_pipe.c\
            sources/freedom.c sources/tokens.c sources/ordering.c\
            sources/exec_new.c  sources/builtins/env.c sources/builtins/lstoarry.c \
            sources/builtins/builtin.c sources/builtins/dir.c \
            sources/builtins/unset.c sources/builtins/export.c  sources/del.c \
			sources/signals.c sources/sub_check.c sources/builtins/exit.c \
			sources/expander/expander.c sources/expander/expand_list.c \
			sources/expander/utils.c sources/expander/expand_heredoc.c \
			sources/builtins/echo.c ${GNL} sources/expander/tokenizer.c \

MINISHELL_ART = \
"\033[32m\n"\
"███╗   ███╗ ██╗ ███╗   ██╗ ██╗ ███████ ╗██╗  ██╗ ███████╗ ██╗      ██╗     \n"\
"████╗ ████║ ██║ ████╗  ██║ ██║ ██╔════ ╝██║  ██║ ██╔════╝ ██║      ██║     \n"\
"██╔████╔██║ ██║ ██╔██╗ ██║ ██║ ███████ ╗███████║ █████╗   ██║      ██║     \n"\
"██║╚██╔╝██║ ██║ ██║╚██╗██║ ██║ ╚════██ ║██╔══██║ ██╔══╝   ██║      ██║     \n"\
"██║ ╚═╝ ██║ ██║ ██║ ╚████║ ██║ ███████ ║██║  ██║ ███████╗ ███████╗ ███████╗\n"\
"╚═╝     ╚═╝ ╚═╝ ╚═╝  ╚═══╝ ╚═╝ ╚══════ ╝╚═╝  ╚═╝ ╚══════╝ ╚══════╝ ╚══════╝\n"\
"						      By: TILLAS & NolYel  \033[0m"

RLFLAGS =	-L/Users/aohssine/goinfre/homebrew/opt/readline/lib -lreadline # tell linker where to look for libs , libs to link 
RLINCLUDE	=	-I/Users/aohssine/goinfre/homebrew/opt/readline/include  # tell compiler where to find headers

# RLFLAGS =	-L/Users/aohssine/.brew/opt/readline/lib -lreadline # tell linker where to look for libs , libs to link 
# RLINCLUDE	=	-I/Users/aohssine/.brew/opt/readline/include  #


CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g
# FFLAG = -fsanitize=address -g

CC = cc
OBJ = $(CFILES:.c=.o)
NAME = minishell
My_lib = lib/libft/libft.a

all : ascii_art $(My_lib) $(NAME)

%.o : %.c Makefile
	$(CC)  $(CFLAGS) $(FFLAG)  $(RLINCLUDE) -c  $< -o $@

$(My_lib) : 
	make -C lib/libft

$(NAME) : $(OBJ) $(My_lib)
	@printf "\033[0;33mGenerating minishell objects... %-33.33s\r \033[0m" $@
	$(CC) $^ $(CFLAGS) $(My_lib) $(RLFLAGS)  -o $@

clean :
	@make clean -C lib/libft
	rm -rf $(OBJ)

ascii_art :
	@echo $(MINISHELL_ART)

fclean : clean
	@make fclean -C lib/libft
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re