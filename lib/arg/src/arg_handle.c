/*
** EPITECH PROJECT, 2024
** arg
** File description:
** arg
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "linked.h"
#include "arg.h"

int arg_as_int(const arg_t *arg)
{
    if (arg && arg->value) {
        return atoi(arg->value);
    } else {
        return 0;
    }
}

float arg_as_float(const arg_t *arg)
{
    if (arg && arg->value) {
        return atof(arg->value);
    } else {
        return 0.0f;
    }
}

char *arg_as_string(const arg_t *arg)
{
    if (arg && arg->value) {
        return arg->value;
    } else {
        return NULL;
    }
}

bool arg_as_bool(const arg_t *arg)
{
    if (arg && arg->value) {
        return (strcmp(arg->value, "true") == 0 ||
            strcmp(arg->value, "1") == 0);
    }
    return false;
}

list_t *arg_as_list(const arg_t *arg, list_t *list)
{
    char *token = NULL;

    if (!arg || !arg->value || !list) {
        return NULL;
    }
    token = strtok(arg->value, " ");
    while (token) {
        list_add_ptr(list, strdup(token));
        token = strtok(NULL, " ");
    }
    return list;
}
