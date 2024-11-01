#include"stdlib.h"
#include"includes/minishell.h"


char *initialize_tokens(int length)
{
    char *tokens = ft_calloc(length + 1, sizeof(char));
    int i = 0;
    while (i <= length) {
        tokens[i] = '0';
        i++;
    }
    return tokens;
}

void process_tokens(char *arg, char *tokens, t_tokens tok)
{
    while (arg[tok.i]) {
        if (arg[tok.i] == '\"' && !tok.in_single_quotes) {
            tokens[tok.i] = 'd';
            tok.in_double_quotes = !tok.in_double_quotes;
        } else if (arg[tok.i] == '\'' && !tok.in_double_quotes) {
            tokens[tok.i] = 's';
            tok.in_single_quotes = !tok.in_single_quotes;
        } else if (!tok.in_single_quotes && !tok.in_double_quotes && 
                   (tok.prevChar == '\'' || tok.prevChar == '\"' || tok.i == 0)) {
            tokens[tok.i] = 'w';
        }
        tok.prevChar = arg[tok.i];
        if (tokens[tok.i] == '0') {
            if (tok.in_double_quotes)
                tokens[tok.i] = 'd';
            else if (tok.in_single_quotes)
                tokens[tok.i] = 's';
            else
                tokens[tok.i] = 'w';
        }
        tok.i++;
    }
    tokens[tok.i] = '\0';
}

char *tokenizer(char *arg)
{
    int len = ft_strlen(arg);
    t_tokens tok;
    tok.in_double_quotes = false;
    tok.in_single_quotes = false;
    tok.prevChar = ' ';
    tok.i = 0;

    char *tokens = initialize_tokens(len);
    process_tokens(arg, tokens, tok);
    return tokens;
}

int count_arg(char *arg)
{
    char *token;
    size_t	i;
    char c ;
	size_t	words;

    token = tokenizer(arg);
    c = ' ';
	words = 0;
	i = 0;
	while (arg[i] == c && token[i] == 'w' )
		i++;
	while (arg[i])
	{
		if (arg[i] == c && arg[i+1] != c && token[i] == 'w' )
			words++;
		i++;
	}
	if (arg[i-1] != c && token[i] != 'w')
		words++;
    free(token);
	return (words);
}

int skip_space_in_word(char *arg, int start)
{
    int i;
    char *token;

    token = tokenizer(arg);
    i = 0;
    while(arg[i+start])
    {
        if(arg[i+start] == ' ' && token[i+start] == 'w')
            i++;
        else{
            free(token);
            return i+start;
        }
    }
    free(token);
    return i+start;
}

int skip_char(char *arg, int start)
{
    int i;
    char *token;

    token = tokenizer(arg);
    i = 0;
    while(arg[i+start])
    {
        if((arg[i+start] == ' ' && token[i+start] == 'w')){
            free(token);
            return i+start;
        }
        i++;
    }
    free(token);
    return i+start;
}
// char **split_arg(char *arg)
// {
//     char **new_arg;
//     int i ;
//     int j ;
//     int looper;

//     if(!arg)
//         return NULL;
//     i = count_arg(arg);
//     new_arg = malloc((i+1) * sizeof(char *));
//     looper = skip_space_in_word(arg, 0);
//     printf("test[%d]\n", looper);
//     j = -1;
//     printf("test 15986 [%s]\n", arg);
//     while(++j < i){
//         printf("test 15986 [%d][%c]-[%d][%c]\n", looper, arg[looper] , skip_char(arg, looper+1) -1 - looper, arg[skip_char(arg, looper+1) -1 - looper] );
//         new_arg[j] = ft_strndup(arg +looper, skip_char(arg, looper+1) -1 - looper);
//         looper = skip_space_in_word(arg, skip_char(arg, looper+1) -1 - looper +1);
//     }
//     new_arg[j] = NULL;
//     return new_arg;
// }

int main(){
        char *str = ft_strdup("  ls  ls\"abde  ss  \"     ");
        char *str1;

        int j = 0;
        int looper = skip_space_in_word(str, 0);
        int end = 0;
        while(j++ < count_arg(str))
        {
            end = skip_char(str, looper +1) +1;
            str1 = ft_strndup(str+looper, end - looper -1);
            puts(str1);
            looper = skip_space_in_word(str, end +1)  ;
        }
}