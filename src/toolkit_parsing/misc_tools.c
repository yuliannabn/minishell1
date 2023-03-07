/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** misc_tools
*/

#include "minishell1.h"

int is_executable(char **exec, char **arg, char **env)
{
    if (is_path_exec(exec, arg, env))
        return (PATH_BIN);
    else if (is_local_exec((*exec)))
        return (LOCAL_BIN);
    return (NONE);
}

bool is_exec_command(char *path)
{
    char *path_cmd = get_path_from_name(path);

    if (is_directory(path_cmd)) {
        free(path_cmd);
        return (true);
    }
    free(path_cmd);
    return (false);
}

void access_error_print(char *program, int *program_return)
{
    print_error(program);
    if ((file_exists(program) && no_permissions(program)))
        print_error(PERSMISSION_DENIED);
    else
        print_error(CMD_NOT_FOUND);
    free(program);
    (*program_return) = BAD_ARG_BUILTIN;
}

void ctrl_c_skip(int signal)
{
    (void) signal;
}

char **get_input_arguments(int prev_ret)
{
    char *input = get_input_string(prev_ret);
    char **args = str_to_word_double(input, " \t");

    if (input)
        free(input);
    return (args);
}
