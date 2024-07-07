/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** vec2_handle
*/

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vec2.h"

void vec2_print(vec2_t vec)
{
    printf("(%d, %d)", vec.x, vec.y);
}

bool vec2_eq(vec2_t a, vec2_t b)
{
    return a.x == b.x && a.y == b.y;
}

bool vec2_ptr_eq(void *v1, void *v2)
{
    return vec2_eq(*(vec2_t *)v1, *(vec2_t *)v2);
}

void *alloc_vec2(void)
{
    vec2_t *vec = NULL;

    vec = malloc(sizeof(vec2_t));
    if (vec)
        memset(vec, 0, sizeof(vec2_t));
    return vec;
}
