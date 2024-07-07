/*
** EPITECH PROJECT, 2024
** arg
** File description:
** arg_flag
*/

#include <string.h>
#include "arg.h"

arg_flag_t arg_flag_type(const char *arg)
{
    size_t len = 0;

    if (!arg)
        return FLAG_NONE;
    len = strlen(arg);
    if (len > 2 && arg[0] == '-' && arg[1] == '-' && arg[2] != '-')
        return FLAG_DOUBLE;
    if (len > 1 && arg[0] == '-' && arg[1] != '-')
        return FLAG_SINGLE;
    return FLAG_NONE;
}

const char *arg_unflag(const char *arg)
{
    arg_flag_t flag = FLAG_NONE;

    flag = arg_flag_type(arg);
    return flag == FLAG_NONE ? NULL : arg + flag;
}
