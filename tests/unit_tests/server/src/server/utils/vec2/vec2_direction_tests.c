/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** vec2_direction_tests
*/

#include <criterion/criterion.h>
#include "server.h"

Test(vec2_rotate_dir_left, rotate_left)
{
    vec2_t vec = {1, 0};
    vec2_t result = vec2_rotate_dir_left(vec);

    cr_assert_eq(result.x, 0);
    cr_assert_eq(result.y, 1);
}

Test(vec2_rotate_dir_right, rotate_right)
{
    vec2_t vec = {1, 0};
    vec2_t result = vec2_rotate_dir_right(vec);

    cr_assert_eq(result.x, 0);
    cr_assert_eq(result.y, -1);
}

Test(vec2_direction_to_id, direction_to_id)
{
    vec2_t vectors[] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
    int ids[] = {1, 5, 3, 7};

    for (int i = 0; i < 4; i++) {
        cr_assert_eq(vec2_direction_to_id(vectors[i]), ids[i]);
    }
}

Test(vec2_rotate_id, rotate_id)
{
    vec2_t up = {0, 1};
    vec2_t down = {0, -1};
    vec2_t left = {-1, 0};
    vec2_t right = {1, 0};

    cr_assert_eq(vec2_rotate_id(1, up, up), 1);
    cr_assert_eq(vec2_rotate_id(3, up, up), 3);
    cr_assert_eq(vec2_rotate_id(5, up, up), 5);
    cr_assert_eq(vec2_rotate_id(7, up, up), 7);

    cr_assert_eq(vec2_rotate_id(1, up, down), 5);
    cr_assert_eq(vec2_rotate_id(3, up, down), 7);
    cr_assert_eq(vec2_rotate_id(5, up, down), 1);
    cr_assert_eq(vec2_rotate_id(7, up, down), 3);

    cr_assert_eq(vec2_rotate_id(1, up, left), 7);
    cr_assert_eq(vec2_rotate_id(3, up, left), 1);
    cr_assert_eq(vec2_rotate_id(5, up, left), 3);
    cr_assert_eq(vec2_rotate_id(7, up, left), 5);

    cr_assert_eq(vec2_rotate_id(1, up, right), 3);
    cr_assert_eq(vec2_rotate_id(3, up, right), 5);
    cr_assert_eq(vec2_rotate_id(5, up, right), 7);
    cr_assert_eq(vec2_rotate_id(7, up, right), 1);
}
