/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** vec2_arithm
*/

#include "vec2.h"

vec2_t vec2_add(vec2_t a, vec2_t b)
{
    return ((vec2_t){a.x + b.x, a.y + b.y});
}

vec2_t vec2_sub(vec2_t a, vec2_t b)
{
    return ((vec2_t){a.x - b.x, a.y - b.y});
}

vec2_t vec2_mul(vec2_t a, vec2_t b)
{
    return ((vec2_t){a.x * b.x, a.y * b.y});
}

vec2_t vec2_div(vec2_t a, vec2_t b)
{
    if (b.x == 0 || b.y == 0)
        return ((vec2_t){0, 0});
    return ((vec2_t){a.x / b.x, a.y / b.y});
}