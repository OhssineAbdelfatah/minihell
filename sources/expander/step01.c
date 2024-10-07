#include"../../includes/minishell.h"

char *getEnvValue(t_env *env, char *key)
{
    while(env != NULL)
    {
        if(ft_strcmp(env->key, key))
            return env->value;
        env = env->next;
    }
    return NULL;
}
bool ft_isspace(char c)
{
    return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r';
}
bool is_special_char(char c) {
    return c == '!' || c == '*' || c == '-' || c == '.';
}

char *expand_env_vars(char *word, t_env *myenv)
{
    char *result = ft_strdup("");
    char *start = word;
    char *end = word;

    while (*end) {
        if (*end == '$') {
            char *before_dollar = ft_strndup(start, end - start);
            char *new_result = malloc(ft_strlen(result) + ft_strlen(before_dollar) + 1);
            ft_strcpy(new_result, result);
            ft_strcat(new_result, before_dollar);
            free(result);
            free(before_dollar);
            result = new_result;

            start = end + 1;
            while (*start && !ft_isspace(*start) && !is_special_char(*start)) {
                start++;
            }
            char *env_name = ft_strndup(end + 1, start - end - 1);
            char *env_value = getEnvValue(myenv, env_name);
            free(env_name);
            if (env_value) {
                new_result = malloc(ft_strlen(result) + ft_strlen(env_value) + 1);
                ft_strcpy(new_result, result);
                ft_strcat(new_result, env_value);
                free(result);
                result = new_result;
            }
            end = start;
        } else {
            end++;
        }
    }

    char *after_last_dollar = ft_strndup(start, end - start);
    char *new_result = malloc(ft_strlen(result) + ft_strlen(after_last_dollar) + 1);
    ft_strcpy(new_result, result);
    ft_strcat(new_result, after_last_dollar);
    free(result);
    free(after_last_dollar);
    result = new_result;

    return result;
}

int countWordPerArg(char *arg) 
{
    int count = 0;
    bool in_word = false;
    bool in_quotes = false;

    while (*arg) {
        if (*arg == '\'' || *arg == '\"') {
            in_quotes = !in_quotes;
        } else if (!in_quotes && ft_isspace(*arg)) {
            if (in_word) {
                count++;
                in_word = false;
            }
        } else if (!in_quotes && *arg == '$') {
            if (in_word) {
                count++;
            }
            in_word = true;
        } else if (!in_word) {
            in_word = true;
        }
        arg++;
    }

    if (in_word) {
        count++;
    }

    return count;
}

char **splitArg(char *arg, t_env *myenv)
{
    int wordCount = countWordPerArg(arg);
    char **words = malloc((wordCount + 1) * sizeof(char *));
    bool in_word = false;
    bool in_quotes = false;
    char *start = arg;
    int index = 0;

    while (*arg) {
        if (*arg == '\'' || *arg == '\"') {
            in_quotes = !in_quotes;
        } else if (!in_quotes && ft_isspace(*arg)) {
            if (in_word) {
                char *word = ft_strndup(start, arg - start);
                char *expanded_word = expand_env_vars(word, myenv);
                free(word);
                words[index] = expanded_word;
                index++;
                in_word = false;
            }
        } else if (!in_quotes && *arg == '$') {
            if (in_word) {
                char *word = ft_strndup(start, arg - start);
                char *expanded_word = expand_env_vars(word, myenv);
                free(word);
                words[index] = expanded_word;
                index++;
            }
            start = arg;
            in_word = true;
        } else if (!in_word) {
            start = arg;
            in_word = true;
        }
        arg++;
    }

    if (in_word) {
        char *word = ft_strndup(start, arg - start);
        char *expanded_word = expand_env_vars(word, myenv);
        free(word);
        words[index] = expanded_word;
        index++;
    }

    words[wordCount] = NULL;  // Null-terminate the array
    return words;
}

int main(int ac, char **av, char** env)
{
    t_env *myenv = init_env(env);
    char *str = ft_strdup("hehe'$HOME'\"$HOME-$SHELL\"$PWD");
    printf("%d \n",countWordPerArg(str) );
    char **dblarg = splitArg(str, myenv);
    int i = -1;
    while(dblarg[++i])
        printf("%s\n",dblarg[i]);    
}