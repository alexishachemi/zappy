/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** player_init
*/

#include <string.h>
#include "player.h"

void init_player(player_t *player)
{
    static size_t id = 0;

    if (!player)
        return;
    memset(player, 0, sizeof(player_t));
    player->id = id;
    player->level = PLAYER_BASE_LEVEL;
    player->lives = PLAYER_LIVES;
    player->elevation_status = ELEV_NONE;
    list_init(&player->elevation_list);
    id++;
}

player_t *create_player(void)
{
    player_t *player = NULL;

    player = malloc(sizeof(player_t));
    init_player(player);
    return player;
}
