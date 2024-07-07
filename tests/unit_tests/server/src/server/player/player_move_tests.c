/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** player_move_tests
*/

#include <criterion/criterion.h>
#include "server.h"

Test(player_right, right)
{
    server_t server = {0};
    player_t player = {0};
    vec2_t current_dir = {1, 0};
    vec2_t expected_dir = {0, -1};

    player.direction = current_dir;
    player_right(&server, &player);
    cr_assert_eq(player.direction.x, expected_dir.x);
    cr_assert_eq(player.direction.y, expected_dir.y);
}

Test(player_left, left)
{
    server_t server = {0};
    player_t player = {0};
    vec2_t current_dir = {1, 0};
    vec2_t expected_dir = {0, 1};

    player.direction = current_dir;
    player_left(&server, &player);
    cr_assert_eq(player.direction.x, expected_dir.x);
    cr_assert_eq(player.direction.y, expected_dir.y);
}

Test(player_forward, forward)
{
    server_t server = {0};
    player_t *player = NULL;
    vec2_t current_pos = {0, 0};
    vec2_t expected_pos = {1, 0};

    world_init(&server, (vec2_t){10, 10}, NULL);
    world_add_team(&server, "Team1");
    world_add_eggs_per_team(&server, 1);
    world_add_player(&server, 1, 0);
    player = world_get_player(&server, 1);
    cr_assert_not_null(player);
    current_pos = player->position;
    expected_pos = vec2_add(current_pos, player->direction);
    expected_pos = world_wrap_pos(expected_pos, server.world.size);
    player_forward(&server, player);
    cr_assert_eq(player->position.x, expected_pos.x);
    cr_assert_eq(player->position.y, expected_pos.y);
    world_deinit(&server);
}
