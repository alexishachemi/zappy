/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** vec2_arithm_tests
*/

#include <criterion/criterion.h>
#include "server.h"

Test(vec2_add, simple_add)
{
    vec2_t vec1 = {1, 2};
    vec2_t vec2 = {3, 4};
    vec2_t result = vec2_add(vec1, vec2);

    cr_assert_eq(result.x, 4);
    cr_assert_eq(result.y, 6);
}

Test(vec2_sub, simple_sub)
{
    vec2_t vec1 = {1, 2};
    vec2_t vec2 = {3, 4};
    vec2_t result = vec2_sub(vec1, vec2);

    cr_assert_eq(result.x, -2);
    cr_assert_eq(result.y, -2);
}

Test(vec2_sub, negative_sub)
{
    vec2_t vec1 = {1, 2};
    vec2_t vec2 = {3, 4};
    vec2_t result = vec2_sub(vec1, vec2);

    cr_assert_eq(result.x, -2);
    cr_assert_eq(result.y, -2);
}

Test(vec2_mul, simple_mul)
{
    vec2_t vec1 = {1, 2};
    vec2_t vec2 = {3, 4};
    vec2_t result = vec2_mul(vec1, vec2);

    cr_assert_eq(result.x, 3);
    cr_assert_eq(result.y, 8);
}

Test(vec2_div, simple_div)
{
    vec2_t vec1 = {1, 2};
    vec2_t vec2 = {3, 4};
    vec2_t result = vec2_div(vec1, vec2);

    cr_assert_eq(result.x, 0);
    cr_assert_eq(result.y, 0);
}

Test(vec2_div, div_by_zero)
{
    vec2_t vec1 = {1, 2};
    vec2_t vec2 = {0, 0};
    vec2_t result = vec2_div(vec1, vec2);

    cr_assert_eq(result.x, 0);
    cr_assert_eq(result.y, 0);
}
