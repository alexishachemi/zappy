/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** world_player
*/

#include "server.h"
#include "gui.h"

static int find_player(list_t *list, int sock)
{
    player_t *player = NULL;

    for (size_t i = 0; i < list_size(list); i++) {
        player = list_at(list, i);
        if (player->sock == sock)
            return i;
    }
    return -1;
}

static bool get_world_index(server_t *server, int sock, int *world_index)
{
    if (!server)
        return false;
    *world_index = find_player(&server->world.players, sock);
    return *world_index != -1;
}

static void apply_layer_remove(player_t *player, egg_t *egg)
{
    if (egg->layer == player)
        egg->layer = NULL;
}

bool world_remove_player(server_t *server, int sock)
{
    int world_index = -1;
    int tile_index = -1;
    player_t *player = NULL;
    tile_t *tile = NULL;

    if (!get_world_index(server, sock, &world_index))
        return false;
    player = list_at(&server->world.players, world_index);
    gui_broadcast_event(server, gui_send_player_death, player);
    tile = world_get_tile(server, player->position);
    tile_index = find_player(&tile->players, sock);
    if (tile_index == -1)
        return false;
    if (player->elevation_status == ELEV_HOST)
        player_cancel_elevation(server, player);
    list_apply(&server->world.eggs, (applicator_t)apply_layer_remove, player);
    SLOG(server, INFO, "Removed Player %d", player->id);
    list_remove(&tile->players, NULL, tile_index);
    list_remove_free(&server->world.players, world_index);
    return true;
}
