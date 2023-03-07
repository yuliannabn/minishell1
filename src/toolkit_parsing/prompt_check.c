/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** prompt_record
*/

#include "minishell1.h"

int execute_prompt(char **arg, char ***env, int *program_return)
{
    char *builtin_list[] = BUILTIN_NAMES;
    char *exec_prompt = str_dup(arg[0]);
    builtin_ptr fnc_array[] = BUILTIN_FNC;

    for (int a = 0; a < BUILTIN_AMOUNT; a++) {
        if (str_equal(builtin_list[a], arg[0])) {
            free(exec_prompt);
            return (fnc_array[a](arg, env, program_return));
        }
    }
    if (try_executable(&exec_prompt, arg, (*env), program_return)) {
        free(exec_prompt);
        return (OK);
    }
    access_error_print(exec_prompt, program_return);
    return (NOT_CMD);
}

int read_input(char ***env)
{
    int status = RUNNING;
    int program_return = 0;
    char **input = NULL;

    while (status >= RUNNING) {
        input = get_input_arguments(program_return);
        status = execute_prompt(input, env, &program_return);
        free(input);
    }
    free_string_array((*env));
    return (program_return);
}
