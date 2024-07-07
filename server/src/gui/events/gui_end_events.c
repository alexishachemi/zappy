/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** gui_end_events
*/

#include <string.h>
#include "gui.h"

bool gui_send_player_death(server_t *server, int sock, void *arg)
{
    char buf[16];
    player_t *player = arg;

    if (!server || !player)
        return false;
    memset(buf, 0, sizeof(buf));
    snprintf(buf, sizeof(buf), "pdi %ld", player->id);
    nets_send(&server->net, sock, buf);
    return true;
}

bool gui_send_game_end(server_t *server, int sock, void *arg)
{
    char buf[32];
    char *team = arg;

    if (!server || !team)
        return false;
    memset(buf, 0, sizeof(buf));
    snprintf(buf, sizeof(buf), "seg %s", team);
    nets_send(&server->net, sock, buf);
    return true;
}

bool gui_send_message(server_t *server, int sock, void *arg)
{
    char buf[1024];
    char *msg = arg;

    if (!server || !msg)
        return false;
    memset(buf, 0, sizeof(buf));
    snprintf(buf, sizeof(buf), "smg %s", msg);
    nets_send(&server->net, sock, buf);
    return true;
}
