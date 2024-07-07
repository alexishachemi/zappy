/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** gui_elev_events
*/

#include <string.h>
#include "gui.h"

bool gui_send_elev_start(server_t *server, int sock, void *arg)
{
    char buf[256];
    player_t *player = arg;
    player_t *participant = NULL;
    vec2_t pos = {0};
    int offset = 0;

    if (!server || !player)
        return false;
    memset(buf, 0, sizeof(buf));
    pos = player->position;
    offset = snprintf(buf, sizeof(buf), "pic %d %d %ld %ld", pos.x, pos.y,
        player->level, player->id);
    for (node_t *n = player->elevation_list.head; n; n = n->next) {
        participant = n->data;
        offset += snprintf(buf + offset, sizeof(buf) - offset, " %ld",
            participant->id);
    }
    nets_send(&server->net, sock, buf);
    return true;
}

bool gui_send_elev_end(server_t *server, int sock, void *arg)
{
    char buf[16];
    elevation_result_t *result = arg;
    vec2_t pos = {0};

    if (!server || !result || !result->host)
        return false;
    pos = result->host->position;
    memset(buf, 0, sizeof(buf));
    snprintf(buf, sizeof(buf), "pie %d %d %d", pos.x, pos.y, result->success);
    nets_send(&server->net, sock, buf);
    return true;
}
