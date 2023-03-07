/*
** EPITECH PROJECT, 2022
** myls
** File description:
** strdup
*/

#include "../../include/pui.h"

char *str_dup(char const *src)
{
    int len = str_len(src);
    char *str = malloc(sizeof(char) * (len + 1));
    int a = 0;

    if (!str || !src)
        return (NULL);
    while (src[a]) {
        str[a] = src[a];
        a++;
    }
    str[a] = '\0';

    return (str);
}

char *cut_string(int from, int to, char *src)
{
    char *new = malloc(sizeof(char) * ((to - from) + 1));

    (void) new, (void) from, (void) to, (void) src;

    return (NULL);
}
