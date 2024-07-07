/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** world_egg_tests
*/

#include <criterion/criterion.h>
#include "server.h"

Test(world_add_egg_randomly, add_egg_randomly)
{
    server_t server = {0};
    egg_t *egg = NULL;

    cr_assert(world_init(&server, (vec2_t){10, 10}, NULL));
    cr_assert(world_add_egg_randomly(&server, 3));
    cr_assert_eq(list_size(&server.world.eggs), 1);
    egg = server.world.eggs.head->data;
    cr_assert_not_null(egg);
    cr_assert_eq(egg->team_id, 3);
    world_deinit(&server);
}

Test(world_add_egg_from_player, add_egg_from_player)
{
    server_t server = {0};
    player_t player = {.team_id = 3, .position = {3, 5}};
    egg_t *egg = NULL;

    cr_assert(world_init(&server, (vec2_t){10, 10}, NULL));
    cr_assert(world_add_egg_from_player(&server, &player));
    cr_assert_eq(list_size(&server.world.eggs), 1);
    egg = server.world.eggs.head->data;
    cr_assert_not_null(egg);
    cr_assert_eq(egg->team_id, 3);
    cr_assert_eq(egg->position.x, player.position.x);
    cr_assert_eq(egg->position.y, player.position.y);
    world_deinit(&server);
}

Test(world_remove_egg, remove_egg)
{
    server_t server = {0};
    player_t player = {.team_id = 3, .position = {3, 5}};

    cr_assert(world_init(&server, (vec2_t){10, 10}, NULL));
    cr_assert(world_add_egg_from_player(&server, &player));
    cr_assert_eq(list_size(&server.world.eggs), 1);
    cr_assert(world_remove_egg(&server, player.position, player.team_id));
    cr_assert_eq(list_size(&server.world.eggs), 0);
    world_deinit(&server);
}

Test(world_remove_tile_eggs, remove_tile_eggs)
{
    server_t server = {0};
    egg_t *egg = NULL;

    cr_assert(world_init(&server, (vec2_t){10, 10}, NULL));
    cr_assert(world_add_egg_randomly(&server, 3));
    cr_assert_eq(list_size(&server.world.eggs), 1);
    egg = server.world.eggs.head->data;
    cr_assert_not_null(egg);
    cr_assert(world_remove_tile_eggs(
        &server, world_get_tile(&server, egg->position)));
    cr_assert_eq(list_size(&server.world.eggs), 0);
    world_deinit(&server);
}

Test(world_add_eggs_per_team, add_eggs_per_team)
{
    server_t server = {0};

    cr_assert(world_init(&server, (vec2_t){10, 10}, NULL));
    cr_assert(world_add_team(&server, "team1"));
    cr_assert(world_add_team(&server, "team2"));
    cr_assert(world_add_team(&server, "team3"));
    cr_assert(world_add_team(&server, "team4"));
    cr_assert(world_add_eggs_per_team(&server, 3));
    cr_assert_eq(list_size(&server.world.eggs), 12);
    world_deinit(&server);
}
