/*
** EPITECH PROJECT, 2023
** server
** File description:
** player_death.c
*/

#include "player.h"
#include "server.h"
#include <string.h>

static void kill_player(server_t *server, player_t *player)
{
    memset(player->jobs, 0, sizeof(job_t) * MAX_JOBS);
    server_kill_player(server, player->sock);
}

void player_update_hunger(server_t *server, player_t *player)
{
    if (server->god_mode)
        return;
    if (player->lives == 0 && player->hunger == 0) {
        kill_player(server, player);
        return;
    }
    if (player->hunger == 0 && player->inventory.food > 0) {
        player->inventory.food--;
        player->hunger = PLAYER_HUNGER;
        return;
    }
    if (player->hunger == 0 && player->inventory.food == 0) {
        player->lives--;
        player->hunger = PLAYER_HUNGER;
        return;
    }
    player->hunger--;
}
