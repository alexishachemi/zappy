/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** world_player_tests
*/

#include <criterion/criterion.h>
#include "server.h"

Test(world_get_player, get_player)
{
    server_t server = {0};
    player_t *player = NULL;

    cr_assert(world_init(&server, (vec2_t){10, 10}, NULL));
    cr_assert(world_add_team(&server, "team1"));
    cr_assert(world_add_team(&server, "team2"));
    cr_assert(world_add_eggs_per_team(&server, 3));
    cr_assert(world_add_player(&server, 1, 0));
    cr_assert(world_add_player(&server, 2, 1));
    cr_assert(world_add_player(&server, 3, 1));
    player = world_get_player(&server, 2);
    cr_assert_not_null(player);
    cr_assert_eq(player->team_id, 1);
    world_deinit(&server);
}

Test(world_get_player, get_null_player)
{
    server_t server = {0};
    player_t *player = NULL;

    cr_assert(world_init(&server, (vec2_t){10, 10}, NULL));
    cr_assert(world_add_team(&server, "team1"));
    cr_assert(world_add_team(&server, "team2"));
    cr_assert(world_add_eggs_per_team(&server, 3));
    cr_assert(world_add_player(&server, 1, 0));
    cr_assert(world_add_player(&server, 2, 1));
    cr_assert(world_add_player(&server, 3, 1));
    player = world_get_player(&server, 4);
    cr_assert_null(player);
    world_deinit(&server);
}

Test(world_add_player, add_player)
{
    server_t server = {0};
    player_t *player = NULL;

    cr_assert(world_init(&server, (vec2_t){10, 10}, NULL));
    cr_assert(world_add_team(&server, "team1"));
    cr_assert(world_add_team(&server, "team2"));
    cr_assert(world_add_eggs_per_team(&server, 3));
    cr_assert_eq(list_size(&server.world.eggs), 6);
    cr_assert_eq(list_size(&server.world.players), 0);
    cr_assert(world_add_player(&server, 1, 0));
    cr_assert(world_add_player(&server, 2, 1));
    cr_assert(world_add_player(&server, 3, 1));
    cr_assert_eq(list_size(&server.world.eggs), 3);
    cr_assert_eq(list_size(&server.world.players), 3);
    player = world_get_player(&server, 2);
    cr_assert_not_null(player);
    cr_assert_eq(player->team_id, 1);
    world_deinit(&server);
}

Test(world_add_player, add_null_player)
{
    server_t server = {0};

    cr_assert(world_init(&server, (vec2_t){10, 10}, NULL));
    cr_assert(world_add_team(&server, "team1"));
    cr_assert(world_add_team(&server, "team2"));
    cr_assert(world_add_eggs_per_team(&server, 3));
    cr_assert_eq(list_size(&server.world.eggs), 6);
    cr_assert_eq(list_size(&server.world.players), 0);
    cr_assert(!world_add_player(&server, 1, 4));
    cr_assert_eq(list_size(&server.world.eggs), 6);
    cr_assert_eq(list_size(&server.world.players), 0);
    world_deinit(&server);
}

Test(world_move_player, move_player)
{
    server_t server = {0};
    player_t *player = NULL;
    tile_t *tile = NULL;

    cr_assert(world_init(&server, (vec2_t){10, 10}, NULL));
    cr_assert(world_add_team(&server, "team1"));
    cr_assert(world_add_team(&server, "team2"));
    cr_assert(world_add_eggs_per_team(&server, 3));
    cr_assert(world_add_player(&server, 1, 0));
    cr_assert(world_add_player(&server, 2, 1));
    cr_assert(world_add_player(&server, 3, 1));
    player = world_get_player(&server, 2);
    cr_assert_not_null(player);
    tile = world_get_tile(&server, (vec2_t){0, 0});
    cr_assert_not_null(tile);
    cr_assert(world_move_player(&server, player, (vec2_t){0, 0}));
    cr_assert_eq(list_size(&tile->players), 1);
    cr_assert_eq(list_size(&server.world.players), 3);
    world_deinit(&server);
}

Test(world_move_player, move_null_player)
{
    server_t server = {0};
    player_t *player = NULL;
    tile_t *tile = NULL;

    cr_assert(world_init(&server, (vec2_t){10, 10}, NULL));
    cr_assert(world_add_team(&server, "team1"));
    cr_assert(world_add_team(&server, "team2"));
    cr_assert(world_add_eggs_per_team(&server, 3));
    cr_assert(world_add_player(&server, 1, 0));
    cr_assert(world_add_player(&server, 2, 1));
    cr_assert(world_add_player(&server, 3, 1));
    player = world_get_player(&server, 2);
    cr_assert_not_null(player);
    tile = world_get_tile(&server, (vec2_t){0, 0});
    cr_assert_not_null(tile);
    cr_assert(!world_move_player(&server, NULL, (vec2_t){0, 0}));
    cr_assert_eq(list_size(&tile->players), 0);
    cr_assert_eq(list_size(&server.world.players), 3);
    world_deinit(&server);
}

Test(world_remove_player, remove_player)
{
    server_t server = {0};
    player_t *player = NULL;
    tile_t *tile = NULL;

    cr_assert(world_init(&server, (vec2_t){10, 10}, NULL));
    cr_assert(world_add_team(&server, "team1"));
    cr_assert(world_add_team(&server, "team2"));
    cr_assert(world_add_eggs_per_team(&server, 3));
    cr_assert(world_add_player(&server, 1, 0));
    cr_assert(world_add_player(&server, 2, 1));
    cr_assert(world_add_player(&server, 3, 1));
    player = world_get_player(&server, 2);
    cr_assert_not_null(player);
    tile = world_get_tile(&server, (vec2_t){0, 0});
    cr_assert_not_null(tile);
    cr_assert(world_remove_player(&server, player->sock));
    cr_assert_eq(list_size(&tile->players), 0);
    cr_assert_eq(list_size(&server.world.players), 2);
    player = world_get_player(&server, 2);
    cr_assert_null(player);
    world_deinit(&server);
}

Test(world_remove_player, remove_null_player)
{
    server_t server = {0};
    player_t *player = NULL;
    tile_t *tile = NULL;

    cr_assert(world_init(&server, (vec2_t){10, 10}, NULL));
    cr_assert(world_add_team(&server, "team1"));
    cr_assert(world_add_team(&server, "team2"));
    cr_assert(world_add_eggs_per_team(&server, 3));
    cr_assert(world_add_player(&server, 1, 0));
    cr_assert(world_add_player(&server, 2, 1));
    cr_assert(world_add_player(&server, 3, 1));
    player = world_get_player(&server, 2);
    cr_assert_not_null(player);
    tile = world_get_tile(&server, (vec2_t){0, 0});
    cr_assert_not_null(tile);
    cr_assert(!world_remove_player(&server, 4));
    cr_assert_eq(list_size(&tile->players), 0);
    cr_assert_eq(list_size(&server.world.players), 3);
    world_deinit(&server);
}
