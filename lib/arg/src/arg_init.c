/*
** EPITECH PROJECT, 2023
** arg
** File description:
** arg initialization
*/

#include <stdlib.h>
#include <string.h>
#include "arg.h"

void argm_init(argm_t *argm)
{
    if (!argm)
        return;
    list_init(&argm->args);
    list_init(&argm->list_expect);
}

void argm_deinit(argm_t *argm)
{
    if (!argm)
        return;
    list_clear(&argm->args, (callback_t)arg_destroy);
    list_clear_free(&argm->list_expect);
}

arg_t *arg_create(const char *name, const char *value)
{
    arg_t *arg = NULL;

    if (!name)
        return NULL;
    arg = malloc(sizeof(arg_t));
    if (!arg)
        return NULL;
    arg->name = strdup(name);
    if (!arg->name) {
        free(arg);
        return NULL;
    }
    arg->value = value ? strdup(value) : NULL;
    if (value && !arg->value) {
        free(arg->name);
        free(arg);
        return NULL;
    }
    return arg;
}

void arg_destroy(arg_t *arg)
{
    if (!arg)
        return;
    if (arg->name)
        free(arg->name);
    if (arg->value)
        free(arg->value);
    free(arg);
}
