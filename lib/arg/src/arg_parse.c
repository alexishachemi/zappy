/*
** EPITECH PROJECT, 2023
** arg
** File description:
** arg parsing
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "arg.h"

static bool str_is_alpha(const char *str)
{
    if (!str)
        return false;
    for (size_t i = 0; str[i]; ++i) {
        if (!(str[i] >= 'a' && str[i] <= 'z')
            && !(str[i] >= 'A' && str[i] <= 'Z'))
            return false;
    }
    return true;
}

bool argm_expect_list(argm_t *argm, const char *name)
{
    char *name_cpy = NULL;

    if (!argm || !name || !str_is_alpha(name))
        return false;
    name_cpy = strdup(name);
    if (!name_cpy)
        return false;
    if (!list_add_ptr(&argm->list_expect, name_cpy)) {
        free(name_cpy);
        return false;
    }
    return true;
}

static bool str_eq(char *s1, char *s2)
{
    return strcmp(s1, s2) == 0;
}

static bool flag_is_list(argm_t *argm, char *name)
{
    if (!argm || !name)
        return false;
    return list_find_if(&argm->list_expect, (comparator_t)str_eq, name);
}

static char *strmcat(char **dest_ptr, const char *src)
{
    size_t dest_size = 0;
    size_t src_size = 0;

    if (!dest_ptr)
        return NULL;
    if (!src || !*src)
        return *dest_ptr;
    dest_size = *dest_ptr ? strlen(*dest_ptr) : 0;
    src_size = strlen(src);
    *dest_ptr = realloc(*dest_ptr, src_size + dest_size + 1);
    if (!*dest_ptr)
        return NULL;
    memset(*dest_ptr + dest_size, 0, src_size);
    return strcat(*dest_ptr, src);
}

static arg_t *argm_add(argm_t *argm, const char *name, const char *value)
{
    arg_t *arg = NULL;

    arg = arg_create(name, value);
    if (!arg)
        return NULL;
    if (!list_add_ptr(&argm->args, arg)) {
        arg_destroy(arg);
        return NULL;
    }
    return arg;
}

static bool parse_arg(argm_t *argm, arg_t **current_arg, const char *current)
{
    arg_flag_t flag = FLAG_NONE;
    bool is_list = false;

    flag = arg_flag_type(current);
    if (flag != FLAG_NONE) {
        *current_arg = argm_add(argm, arg_unflag(current), NULL);
        return *current_arg != NULL;
    }
    if (flag == FLAG_NONE && *current_arg) {
        is_list = flag_is_list(argm, (*current_arg)->name);
        if ((is_list && (*current_arg)->value)
            && !strmcat(&(*current_arg)->value, " "))
            return false;
        if (!strmcat(&(*current_arg)->value, current))
            return false;
        if (!is_list)
            *current_arg = NULL;
    }
    return true;
}

bool argm_parse(argm_t *argm, size_t args_len, const char **args)
{
    arg_iterator_t iter;
    arg_t *current_arg = NULL;
    const char *current = NULL;

    if (!argm || !arg_iterator_init(&iter, args_len, args))
        return false;
    current = arg_iterator_next(&iter);
    while (current) {
        if (!parse_arg(argm, &current_arg, current))
            return false;
        current = arg_iterator_next(&iter);
    }
    return true;
}

const arg_t *argm_get(const argm_t *argm, const char *name)
{
    arg_t *arg = NULL;

    if (!argm || !name) {
        return NULL;
    }
    for (node_t *node = argm->args.head; node; node = node->next) {
        arg = (arg_t *)node->data;
        if (strcmp(arg->name, name) == 0) {
            return arg;
        }
    }
    return NULL;
}

bool argm_has(const argm_t *argm, const char *name)
{
    if (argm_get(argm, name) != NULL) {
        return true;
    } else {
        return false;
    }
}
