/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** player_init_tests
*/

#include <criterion/criterion.h>
#include "server.h"

Test(init_player, init)
{
    player_t player = {0};

    init_player(&player);
    cr_assert_eq(player.level, PLAYER_BASE_LEVEL);
    cr_assert_eq(player.lives, PLAYER_LIVES);
    cr_assert_eq(player.elevation_status, ELEV_NONE);
}
