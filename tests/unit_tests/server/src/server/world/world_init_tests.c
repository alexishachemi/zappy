/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** world_init_tests
*/

#include <criterion/criterion.h>
#include "server.h"

Test(world_init, init_world)
{
    server_t server = {0};

    cr_assert(world_init(&server, (vec2_t){10, 10}, NULL));
    cr_assert_eq(server.world.size.x, 10);
    cr_assert_eq(server.world.size.y, 10);
    cr_assert_eq(list_size(&server.world.players), 0);
    cr_assert_eq(list_size(&server.world.eggs), 0);
    cr_assert_eq(list_size(&server.world.teams), 0);
    cr_assert_neq(server.world.map, NULL);
    world_deinit(&server);
}

Test(world_deinit, deinit_world)
{
    server_t server = {0};

    cr_assert(world_init(&server, (vec2_t){10, 10}, NULL));
    world_add_team(&server, "team1");
    world_add_team(&server, "team2");
    world_add_eggs_per_team(&server, 2);
    world_add_player(&server, 1, 0);
    world_add_player(&server, 2, 0);
    world_add_player(&server, 3, 1);
    cr_assert_eq(list_size(&server.world.players), 3);
    cr_assert_eq(list_size(&server.world.eggs), 1);
    cr_assert_eq(list_size(&server.world.teams), 2);
    world_deinit(&server);
    cr_assert_eq(list_size(&server.world.players), 0);
    cr_assert_eq(list_size(&server.world.eggs), 0);
    cr_assert_eq(list_size(&server.world.teams), 0);
    cr_assert_null(server.world.map);
}
