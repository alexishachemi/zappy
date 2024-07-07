/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** world_update
*/

#include "server.h"

bool world_set_freq(server_t *server, int freq)
{
    if (!server || freq <= 0)
        return false;
    server->world.freq = freq;
    return true;
}

bool world_update(server_t *server)
{
    if (server->world.spawn_timer == 0) {
        server->world.spawn_timer = RESSOURCE_SPAWN_RATE;
        world_spawn_ressources(server);
    } else {
        server->world.spawn_timer--;
    }
    player_update(server);
    return true;
}
