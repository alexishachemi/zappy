/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** player_elevate_tests
*/

#include <criterion/criterion.h>
#include "server.h"

Test(player_elevate, elevate)
{
    player_t player = {0};

    player.elevation_status = ELEV_HOST;
    cr_assert(player_elevate(NULL, &player));
    cr_assert_eq(player.elevation_status, ELEV_NONE);
    cr_assert_eq(player.level, 1);
}

Test(player_elevate, elevate_not_host)
{
    player_t player = {0};

    player.elevation_status = ELEV_NONE;
    cr_assert_not(player_elevate(NULL, &player));
    cr_assert_eq(player.elevation_status, ELEV_NONE);
    cr_assert_eq(player.level, 0);
}

Test(player_elevate, elevate_null)
{
    cr_assert_not(player_elevate(NULL, NULL));
}

Test(player_cancel_elevation, cancel)
{
    player_t player = {0};

    player.elevation_status = ELEV_HOST;
    cr_assert(player_cancel_elevation(NULL, &player));
    cr_assert_eq(player.elevation_status, ELEV_NONE);
    cr_assert_eq(player.level, 0);
}

Test(player_cancel_elevation, cancel_not_host)
{
    player_t player = {0};

    player.elevation_status = ELEV_NONE;
    cr_assert_not(player_cancel_elevation(NULL, &player));
    cr_assert_eq(player.elevation_status, ELEV_NONE);
    cr_assert_eq(player.level, 0);
}

Test(player_cancel_elevation, cancel_null)
{
    cr_assert_not(player_cancel_elevation(NULL, NULL));
}
