/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** world_player_get
*/

#include "server.h"
#include "utils.h"

player_t *world_get_player(server_t *server, int sock)
{
    if (!server)
        return NULL;
    return list_find_if(&server->world.players, player_sock_eq, &sock);
}

player_t *world_get_player_by_id(server_t *server, size_t id)
{
    if (!server)
        return NULL;
    return list_find_if(&server->world.players, player_id_eq, &id);
}
