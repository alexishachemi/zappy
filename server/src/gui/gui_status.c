/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** gui_status
*/

#include "gui.h"

bool gui_send_current_state(server_t *server, int sock)
{
    egg_t *egg = NULL;

    if (!server)
        return false;
    gui_send_map_size(server, sock, NULL);
    gui_send_time_unit(server, sock, NULL);
    gui_send_map_info(server, sock, NULL);
    gui_send_teams_name(server, sock, NULL);
    for (node_t *n = server->world.players.head; n; n = n->next) {
        gui_send_new_player(server, sock, n->data);
        gui_send_player_inv(server, sock, n->data);
    }
    for (node_t *n = server->world.eggs.head; n; n = n->next) {
        egg = n->data;
        if (egg->layer)
            gui_send_egg_lay_end(server, sock, egg);
    }
    return true;
}

void gui_send_bad_arg(server_t *server, int sock)
{
    if (!server)
        return;
    nets_send(&server->net, sock, "sbd");
}

void gui_send_unknown_cmd(server_t *server, int sock)
{
    if (!server)
        return;
    nets_send(&server->net, sock, "suc");
}
