/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** world_team_tests
*/

#include <criterion/criterion.h>
#include "server.h"

Test(world_add_team, add_team)
{
    server_t server = {0};

    cr_assert(world_init(&server, (vec2_t){10, 10}, NULL));
    cr_assert(list_empty(&server.world.teams));
    world_add_team(&server, "team1");
    cr_assert_eq(list_size(&server.world.teams), 1);
    world_add_team(&server, "team2");
    cr_assert_eq(list_size(&server.world.teams), 2);
    cr_assert_str_eq(((team_t *)list_at(&server.world.teams, 0))->name, "team1");
    cr_assert_str_eq(((team_t *)list_at(&server.world.teams, 1))->name, "team2");
    world_deinit(&server);
}

Test(world_add_teams, add_teams)
{
    server_t server = {0};
    list_t teams = {0};

    list_init(&teams);
    list_add_ptr(&teams, "team1");
    list_add_ptr(&teams, "team2");
    list_add_ptr(&teams, "team3");
    cr_assert(world_init(&server, (vec2_t){10, 10}, NULL));
    cr_assert(list_empty(&server.world.teams));
    cr_assert(world_add_teams(&server, &teams));
    cr_assert_eq(list_size(&server.world.teams), 3);
    cr_assert_str_eq(((team_t *)list_at(&server.world.teams, 0))->name, "team1");
    cr_assert_str_eq(((team_t *)list_at(&server.world.teams, 1))->name, "team2");
    cr_assert_str_eq(((team_t *)list_at(&server.world.teams, 2))->name, "team3");
    world_deinit(&server);
}

Test(world_add_teams, add_teams_fail)
{
    server_t server = {0};
    list_t teams = {0};

    list_init(&teams);
    cr_assert(world_init(&server, (vec2_t){10, 10}, NULL));
    cr_assert(list_empty(&server.world.teams));
    cr_assert(world_add_teams(&server, &teams));
    cr_assert(list_empty(&server.world.teams));
    list_clear_free(&teams);
    world_deinit(&server);
}

Test(world_get_team_id, get_team_id)
{
    server_t server = {0};

    cr_assert(world_init(&server, (vec2_t){10, 10}, NULL));
    world_add_team(&server, "team1");
    world_add_team(&server, "team2");
    world_add_team(&server, "team3");
    cr_assert_eq(world_get_team_id(&server, "team1"), 0);
    cr_assert_eq(world_get_team_id(&server, "team2"), 1);
    cr_assert_eq(world_get_team_id(&server, "team3"), 2);
    cr_assert_eq(world_get_team_id(&server, "team4"), -1);
    world_deinit(&server);
}
