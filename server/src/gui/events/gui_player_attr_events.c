/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** gui_cmd_player
*/

#include <string.h>
#include "gui.h"
#include "utils.h"

bool gui_send_teams_name(server_t *server, int sock, UNUSED void *arg)
{
    team_t *team = NULL;
    char buf[32];

    if (!server)
        return false;
    memset(buf, 0, sizeof(buf));
    for (node_t *n = server->world.teams.head; n; n = n->next) {
        team = n->data;
        snprintf(buf, 32, "tna %s", team->name);
        nets_send(&server->net, sock, buf);
    }
    return true;
}

bool gui_send_player_pos(server_t *server, int sock, void *arg)
{
    char buf[16];
    player_t *player = arg;

    if (!server || !player)
        return false;
    memset(buf, 0, sizeof(buf));
    snprintf(
        buf, sizeof(buf), "ppo %ld %d %d %d", player->id, player->position.x,
        player->position.y, vec2_dir_to_gui_orientation(player->direction)
    );
    nets_send(&server->net, sock, buf);
    return true;
}

bool gui_send_player_level(server_t *server, int sock, void *arg)
{
    char buf[16];
    player_t *player = arg;

    if (!server || !player)
        return false;
    memset(buf, 0, sizeof(buf));
    snprintf(buf, sizeof(buf), "plv %ld %ld", player->id, player->level);
    nets_send(&server->net, sock, buf);
    return true;
}

bool gui_send_player_inv(server_t *server, int sock, void *arg)
{
    char buf[128];
    player_t *player = arg;
    inventory_t *inv = NULL;

    if (!server || !player)
        return false;
    memset(buf, 0, sizeof(buf));
    inv = &player->inventory;
    snprintf(
        buf, sizeof(buf), "pin %ld %d %d %ld %ld %ld %ld %ld %ld %ld",
        player->id, player->position.x, player->position.y,
        inv->food, inv->linemate, inv->deraumere, inv->sibur,
        inv->mendiane, inv->phiras, inv->thystame
    );
    nets_send(&server->net, sock, buf);
    return true;
}
