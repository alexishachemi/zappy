/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** world_directions_tests
*/

#include <criterion/criterion.h>
#include "server.h"

Test(world_get_direction, simple_direction)
{
    server_t server = {0};
    vec2_t from = {0, 0};
    vec2_t to = {1, 0};
    vec2_t up = {0, 1};

    cr_assert(world_init(&server, (vec2_t){10, 10}, NULL));
    cr_assert_eq(world_get_direction(&server, from, to, up), 7);
    world_deinit(&server);
}

Test(world_get_direction, wrap_around_direction)
{
    server_t server = {0};
    vec2_t from = {0, 8};
    vec2_t to = {8, 8};
    vec2_t up = {-1, 0};

    cr_assert(world_init(&server, (vec2_t){10, 10}, NULL));
    cr_assert_eq(world_get_direction(&server, from, to, up), 1);
    world_deinit(&server);
}

Test(world_get_direction, diagonal_direction)
{
    server_t server = {0};
    vec2_t from = {0, 0};
    vec2_t to = {1, 1};
    vec2_t up = {0, 1};

    cr_assert(world_init(&server, (vec2_t){10, 10}, NULL));
    cr_assert_eq(world_get_direction(&server, from, to, up), 8);
    world_deinit(&server);
}

Test(world_get_direction, diagonal_wrap_around_direction)
{
    server_t server = {0};
    vec2_t from = {0, 8};
    vec2_t to = {8, 0};
    vec2_t up = {0, -1};

    cr_assert(world_init(&server, (vec2_t){10, 10}, NULL));
    cr_assert_eq(world_get_direction(&server, from, to, up), 6);
    world_deinit(&server);
}
