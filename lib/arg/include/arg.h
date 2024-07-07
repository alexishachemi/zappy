/*
** EPITECH PROJECT, 2024
** arg
** File description:
** header
*/

#pragma once

#include "linked.h"

typedef enum {
    FLAG_NONE,
    FLAG_SINGLE,
    FLAG_DOUBLE,
} arg_flag_t;

typedef struct {
    char *name;
    char *value;
} arg_t;

typedef struct {
    list_t args;
    list_t list_expect;
} argm_t;

typedef struct {
    size_t args_len;
    const char **args;
    size_t current_index;
} arg_iterator_t;

// arg_t

void argm_init(argm_t *argm);
void argm_deinit(argm_t *argm);
bool argm_expect_list(argm_t *argm, const char *name);
bool argm_parse(argm_t *argm, size_t args_len, const char **args);
const arg_t *argm_get(const argm_t *argm, const char *name);
bool argm_has(const argm_t *argm, const char *name);

// argm_t

arg_t *arg_create(const char *name, const char *value);
void arg_destroy(arg_t *arg);
int arg_as_int(const arg_t *arg);
float arg_as_float(const arg_t *arg);
char *arg_as_string(const arg_t *arg);
bool arg_as_bool(const arg_t *arg);
list_t *arg_as_list(const arg_t *arg, list_t *list);

// arg_iterator_t

bool arg_iterator_init(arg_iterator_t *iter,
    size_t args_len, const char **args);
const char *arg_iterator_next(arg_iterator_t *iter);

// arg_flag_t

const char *arg_unflag(const char *arg);
arg_flag_t arg_flag_type(const char *arg);
