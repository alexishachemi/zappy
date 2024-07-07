/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** world_ressources_tests
*/

#include <criterion/criterion.h>
#include "world.h"
#include "server_tests_utils.h"

Test(world_count_items, count_items)
{
    server_t server = {0};
    tile_t *tile = NULL;
    inventory_t ressources = {0};
    vec2_t size = {10, 10};
    inventory_t initial = {0};
    inventory_t expected = {
        .food = 3,
        .linemate = 0,
        .deraumere = 0,
        .sibur = 1,
        .mendiane = 0,
        .phiras = 0,
        .thystame = 0,
    };

    cr_assert(world_init(&server, size, NULL));
    ressources = world_count_items(&server);
    cr_assert(inventory_eq(&ressources, &initial));
    tile = world_get_tile(&server, (vec2_t){0, 0});
    cr_assert_not_null(tile);
    tile->inventory.food = 1;
    tile->inventory.sibur = 1;
    tile = world_get_tile(&server, (vec2_t){0, 1});
    cr_assert_not_null(tile);
    tile->inventory.food = 1;
    tile = world_get_tile(&server, (vec2_t){1, 0});
    cr_assert_not_null(tile);
    tile->inventory.food = 1;
    ressources = world_count_items(&server);
    cr_assert(inventory_eq(&ressources, &expected));
    world_deinit(&server);
}

Test(world_spawn_item, spawn_item)
{
    server_t server = {0};
    inventory_t ressources = {0};
    vec2_t size = {10, 10};
    inventory_t initial = {0};
    inventory_t expected = {
        .food = 1,
        .linemate = 0,
        .deraumere = 0,
        .sibur = 0,
        .mendiane = 0,
        .phiras = 0,
        .thystame = 0,
    };

    cr_assert(world_init(&server, size, NULL));
    ressources = world_count_items(&server);
    cr_assert(inventory_eq(&ressources, &initial));
    cr_assert(world_spawn_item(&server, FOOD, 1, NULL));
    ressources = world_count_items(&server);
    cr_assert(inventory_eq(&ressources, &expected));
    world_deinit(&server);
}

Test(world_spawn_ressources, spawn_ressources)
{
    server_t server = {0};
    inventory_t ressources = {0};
    inventory_t initial = {0};
    vec2_t size = {10, 10};
    inventory_t expected = {
        .food = size.x * size.y * 0.5,
        .linemate = size.x * size.y * 0.3,
        .deraumere = size.x * size.y * 0.15,
        .sibur = size.x * size.y * 0.1,
        .mendiane = size.x * size.y * 0.1,
        .phiras = size.x * size.y * 0.08,
        .thystame = size.x * size.y * 0.05,
    };

    cr_assert(world_init(&server, size, NULL));
    ressources = world_count_items(&server);
    cr_assert(inventory_eq(&ressources, &initial));
    cr_assert(world_spawn_ressources(&server));
    ressources = world_count_items(&server);
    cr_assert(inventory_eq(&ressources, &expected));
    world_deinit(&server);
}
