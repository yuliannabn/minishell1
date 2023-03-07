/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** execute_binary
*/

#include "minishell1.h"

void print_signal_out(int ret)
{
    int ext_code = WTERMSIG(ret);

    if (ext_code == SIGBUS || ext_code == SIGSEGV)
        print_error(strsignal(WTERMSIG(ret)));
    if (ext_code == SIGABRT)
        print_error("Abort");
    if (ext_code == SIGFPE)
        print_error("Floating exception");
    if (WCOREDUMP(ret))
        print_error(COREDUMPED);
    print_error("\n");
}

bool is_printable_signal(int program_return)
{
    int sigs[] = {SIGBUS, SIGSEGV, SIGABRT, SIGFPE};
    int a = 0;

    while (a < SIG_AMT) {
        if (WTERMSIG(program_return) == sigs[a])
            return (true);
        a++;
    }
    return (false);
}

bool no_permissions(char *program)
{
    if (access(program, R_OK) <= ERROR)
        return (true);
    if (access(program, X_OK) <= ERROR)
        return (true);
    if (access(program, W_OK) <= ERROR)
        return (true);
    return (false);
}

int execute_binary(char *exec, char **arg, char **env, int *program_return)
{
    pid_t child = fork();

    if (child == 0) {
        if (((*program_return) = execve(exec, arg, env)) == -1) {
            print_error(exec), print_error(": "),
            print_error(strerror(errno));
            print_error(". Binary file not executable.\n");
            exit ((*program_return) = BAD_ARG_BUILTIN);
        }
    } else
        waitpid(child, program_return, WUNTRACED);
    if (WIFEXITED((*program_return)))
        (*program_return) = WEXITSTATUS((*program_return));
    if (is_printable_signal((*program_return)))
        print_signal_out((*program_return)), (*program_return) = OK;
    return ((*program_return));
}

bool try_executable(char **exec, char **arg, char **env, int *program_return)
{
    int exec_status = (is_executable(exec, arg, env));

    if (exec_status == NONE || is_directory((*exec))) {
        return (false);
    } else
        execute_binary((*exec), arg, env, program_return);
    return (true);
}
