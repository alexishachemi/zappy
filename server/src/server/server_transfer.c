/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** server_standby
*/

#include "server.h"
#include "gui.h"
#include "utils.h"

static void welcome_clients(server_t *server)
{
    int sock = 0;

    while (nets_accept_incoming(&server->net, &sock)) {
        server_add_playerless(server, sock);
    }
}

static void handle_outgoing(server_t *server)
{
    int sock = 0;

    while (nets_accept_outgoing(&server->net, &sock)) {
        server_remove_client(server, sock);
    }
}

static bool handle_non_standby(server_t *server, int sock, char *str)
{
    player_t *player = NULL;

    player = world_get_player(server, sock);
    if (player) {
        player_schedule_job(server, player, str);
        free(str);
        return true;
    }
    if (list_find_if(&server->graphical_clients, int_eq, &sock)) {
        gui_process_command(server, sock, str);
        free(str);
        return true;
    }
    return false;
}

void server_handle_clients(server_t *server)
{
    net_transfer_t transfer = {0};

    if (!server)
        return;
    welcome_clients(server);
    handle_outgoing(server);
    while (nets_recv(&server->net, &transfer)) {
        if (handle_non_standby(server, transfer.sock, transfer.data))
            continue;
        if (!server_try_add_gui(server, transfer.sock, transfer.data))
            server_try_add_player(server, transfer.sock, transfer.data);
        free(transfer.data);
    }
}
