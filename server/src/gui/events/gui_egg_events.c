/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** gui_egg_events
*/

#include <string.h>
#include "gui.h"

bool gui_send_egg_lay_start(server_t *server, int sock, void *arg)
{
    char buf[16];
    player_t *player = arg;

    if (!server || !player)
        return false;
    memset(buf, 0, sizeof(buf));
    snprintf(buf, sizeof(buf), "pfk %ld", player->id);
    nets_send(&server->net, sock, buf);
    return true;
}

bool gui_send_egg_lay_end(server_t *server, int sock, void *arg)
{
    char buf[16];
    egg_t *egg = arg;
    vec2_t pos = {0};
    long layer_id = 0;

    if (!server || !egg)
        return false;
    memset(buf, 0, sizeof(buf));
    layer_id = egg->layer ? (long)egg->layer->id : -1;
    pos = egg->position;
    snprintf(buf, sizeof(buf), "enw %ld %ld %d %d", egg->id, layer_id,
        pos.x, pos.y);
    nets_send(&server->net, sock, buf);
    return true;
}

bool gui_send_player_from_egg(server_t *server, int sock, void *arg)
{
    char buf[16];
    egg_t *egg = arg;

    if (!server || !egg)
        return false;
    memset(buf, 0, sizeof(buf));
    snprintf(buf, sizeof(buf), "ebo %ld", egg->id);
    nets_send(&server->net, sock, buf);
    return true;
}

bool gui_send_egg_death(server_t *server, int sock, void *arg)
{
    char buf[16];
    egg_t *egg = arg;

    if (!server || !egg)
        return false;
    memset(buf, 0, sizeof(buf));
    snprintf(buf, sizeof(buf), "edi %ld", egg->id);
    nets_send(&server->net, sock, buf);
    return true;
}
