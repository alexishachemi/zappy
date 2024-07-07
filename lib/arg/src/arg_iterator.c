/*
** EPITECH PROJECT, 2024
** arg
** File description:
** arg_iterator
*/

#include "arg.h"

bool arg_iterator_init(arg_iterator_t *iter,
    size_t args_len, const char **args)
{
    if (!iter || !args)
        return false;
    iter->args = args;
    iter->args_len = args_len;
    iter->current_index = 0;
    return true;
}

const char *arg_iterator_next(arg_iterator_t *iter)
{
    const char *arg = NULL;

    if (!iter || iter->current_index >= iter->args_len)
        return NULL;
    arg = iter->args[iter->current_index];
    iter->current_index++;
    return arg;
}
