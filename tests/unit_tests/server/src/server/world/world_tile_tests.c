/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** world_tile_tests
*/

#include <criterion/criterion.h>
#include "server.h"

Test(world_wrap_pos, simple_wrap)
{
    vec2_t pos = {0, 0};
    vec2_t size = {10, 10};
    vec2_t result = world_wrap_pos(pos, size);

    cr_assert_eq(result.x, 0);
    cr_assert_eq(result.y, 0);
}

Test(world_wrap_pos, negative_wrap)
{
    vec2_t pos = {-1, -1};
    vec2_t size = {10, 10};
    vec2_t result = world_wrap_pos(pos, size);

    cr_assert_eq(result.x, 9);
    cr_assert_eq(result.y, 9);
}

Test(world_wrap_pos, big_wrap)
{
    vec2_t pos = {100, 100};
    vec2_t size = {10, 10};
    vec2_t result = world_wrap_pos(pos, size);

    cr_assert_eq(result.x, 0);
    cr_assert_eq(result.y, 0);
}

Test(world_get_tile, simple_get)
{
    server_t server = {0};
    tile_t *tile = NULL;

    cr_assert(world_init(&server, (vec2_t){10, 10}, NULL));
    tile = world_get_tile(&server, (vec2_t){3, 2});
    cr_assert_eq(tile, server.world.map[2] + 3);
}

Test(world_get_tile, negative_get)
{
    server_t server = {0};
    tile_t *tile = NULL;

    cr_assert(world_init(&server, (vec2_t){10, 10}, NULL));
    tile = world_get_tile(&server, (vec2_t){-1, -1});
    cr_assert_eq(tile, server.world.map[9] + 9);
}

Test(world_get_tile, big_get)
{
    server_t server = {0};
    tile_t *tile = NULL;

    cr_assert(world_init(&server, (vec2_t){10, 10}, NULL));
    tile = world_get_tile(&server, (vec2_t){100, 100});
    cr_assert_eq(tile, server.world.map[0] + 0);
}

Test(world_get_random_tile, simple_get)
{
    server_t server = {0};
    tile_t *tile = NULL;
    vec2_t pos = {-1, -1};

    cr_assert(world_init(&server, (vec2_t){10, 10}, NULL));
    tile = world_get_random_tile(&server, &pos);
    cr_assert_not_null(tile);
    cr_assert(pos.x >= 0 && pos.x < 10);
    cr_assert(pos.y >= 0 && pos.y < 10);
}

Test(world_get_random_tile, null_get)
{
    tile_t *tile = NULL;
    vec2_t pos = {-1, -1};

    tile = world_get_random_tile(NULL, &pos);
    cr_assert_null(tile);
    cr_assert_eq(pos.x, -1);
    cr_assert_eq(pos.y, -1);
}
