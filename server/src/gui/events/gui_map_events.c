/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** gui_cmd_map
*/

#include <string.h>
#include "gui.h"
#include "utils.h"

bool gui_send_map_size(server_t *server, int sock, UNUSED void *arg)
{
    char buf[32];

    if (!server)
        return false;
    memset(buf, 0, 32);
    snprintf(buf, 32, "msz %d %d", server->world.size.x, server->world.size.y);
    nets_send(&server->net, sock, buf);
    return true;
}

bool gui_send_tile_info(server_t *server, int sock, void *arg)
{
    char buf[126];
    vec2_t *pos = arg;
    inventory_t *inv = NULL;
    tile_t *tile = NULL;

    if (!server || !pos)
        return false;
    tile = world_get_tile(server, *pos);
    if (!tile)
        return false;
    memset(buf, 0, sizeof(buf));
    inv = &tile->inventory;
    snprintf(buf, sizeof(buf), "bct %d %d %ld %ld %ld %ld %ld %ld %ld", pos->x,
        pos->y, inv->food, inv->linemate, inv->deraumere, inv->sibur,
        inv->mendiane, inv->phiras, inv->thystame);
    nets_send(&server->net, sock, buf);
    return true;
}

bool gui_send_map_info(server_t *server, int sock, UNUSED void *arg)
{
    vec2_t pos = {0};
    bool status = true;

    if (!server)
        return false;
    for (int y = 0; status && y < server->world.size.y; y++) {
        for (int x = 0; status && x < server->world.size.x; x++) {
            pos = (vec2_t){x, y};
            status = gui_send_tile_info(server, sock, &pos);
        }
    }
    return status;
}
