/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** gui_event_player
*/

#include <string.h>
#include "gui.h"

bool gui_send_new_player(server_t *server, int sock, void *arg)
{
    char buf[32];
    player_t *player = arg;
    int dir = 0;
    vec2_t pos = {0};
    const char *team_name = NULL;

    if (!server || !player)
        return false;
    memset(buf, 0, sizeof(buf));
    team_name = world_get_team_name(server, player->team_id);
    dir = vec2_dir_to_gui_orientation(player->direction);
    pos = player->position;
    if (!team_name || dir < 0)
        return false;
    snprintf(buf, sizeof(buf), "pnw %ld %d %d %d %ld %s", player->id,
        pos.x, pos.y, dir, player->level, team_name);
    nets_send(&server->net, sock, buf);
    return true;
}

bool gui_send_expulsion(server_t *server, int sock, void *arg)
{
    char buf[32];
    player_t *player = arg;

    if (!server || !player)
        return false;
    memset(buf, 0, sizeof(buf));
    snprintf(buf, sizeof(buf), "pex %ld", player->id);
    nets_send(&server->net, sock, buf);
    return true;
}

bool gui_send_broadcast(server_t *server, int sock, void *arg)
{
    char buf[1024];
    broadcaster_t *bc = arg;

    if (!server || !bc)
        return false;
    memset(buf, 0, sizeof(buf));
    snprintf(buf, sizeof(buf), "pbc %ld %s", bc->emitter->id, bc->msg);
    nets_send(&server->net, sock, buf);
    return true;
}
