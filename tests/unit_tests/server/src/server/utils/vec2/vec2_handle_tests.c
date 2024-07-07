/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** vec2_handle_tests
*/

#include <criterion/criterion.h>
#include "server.h"

Test(vec2_eq, simple_eq)
{
    vec2_t a = {0, 0};
    vec2_t b = {0, 0};

    cr_assert(vec2_eq(a, b));
}

Test(vec2_eq, negative_eq)
{
    vec2_t a = {0, 0};
    vec2_t b = {1, 1};

    cr_assert_not(vec2_eq(a, b));
}
