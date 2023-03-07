/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** parse_arguments
*/

#include "minishell1.h"

char *get_input_string(int prev_ret)
{
    size_t size = 0;
    int len = 0;
    char *buf = NULL;

    signal(SIGINT, ctrl_c_skip);
    while (len < 2 && len > ERROR) {
        if (isatty(STDIN_FILENO))
            prompt_wait(prev_ret);
        len = getline(&buf, &size, stdin);
        if (len == END_OF_FILE)
            return (str_dup(EXIT_MYSHELL));
    }
    remove_enter(&buf, len);
    return (buf);
}

bool strcmp_from_prompt(char *prompt, char *str, char lookup)
{
    int search_len = str_len(prompt);
    int a = 0;

    while ((prompt && str) && prompt[a] == str[a])
        a++;
    if (a == search_len && str[search_len] == lookup)
        return (true);
    return (false);
}

char *get_var_content_string(char *index)
{
    char *var_content = NULL;
    char **full_var = str_to_word(index, '=');

    if (full_var[1])
        var_content = str_dup(full_var[1]);
    else
        var_content = str_dup(EMPTY);
    free_string_array(full_var);
    return (var_content);
}

char *find_env_var(char *prompt, char **env)
{
    int a = 0;

    while (env[a]) {
        if (strcmp_from_prompt(prompt, env[a], '='))
            return (get_var_content_string(env[a]));
        a++;
    }
    return (NULL);
}

char **find_env_var_ptr(char *prompt, char **env)
{
    int a = 0;

    while (env[a]) {
        if (strcmp_from_prompt(prompt, env[a], '='))
            return (&env[a]);
        a++;
    }
    return (NULL);
}
