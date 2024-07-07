/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** server_standby_test
*/

#include <criterion/criterion.h>
#include "server.h"

Test(server_try_add_player, bad_team)
{
    server_t server = {0};
    const char *team_name = "yellow";

    world_init(&server, (vec2_t){10, 10}, NULL);
    cr_assert(world_add_team(&server, "blue"));
    cr_assert(world_add_eggs_per_team(&server, 1));
    cr_assert_not(server_try_add_player(&server, 1, team_name));
    world_deinit(&server);
}

Test(server_try_add_player, good_team)
{
    server_t server = {0};
    const char *team_name = "blue";

    world_init(&server, (vec2_t){10, 10}, NULL);
    cr_assert(world_add_team(&server, "blue"));
    cr_assert(world_add_eggs_per_team(&server, 1));
    cr_assert(server_try_add_player(&server, 1, team_name));
    world_deinit(&server);
}
