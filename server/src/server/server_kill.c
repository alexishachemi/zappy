/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** server_kill.c
*/

#include "server.h"
#include "gui.h"

static int get_player_client_index(list_t *player_list, int sock)
{
    int index = 0;

    for (node_t *n = player_list->head; n; n = n->next) {
        if (((player_t *)n->data)->sock == sock)
            return index;
        index++;
    }
    return -1;
}

bool server_kill_player(server_t *server, int sock)
{
    int index_client = -1;
    player_t *player = NULL;

    if (!server)
        return false;
    player = world_get_player(server, sock);
    if (!player)
        return false;
    world_remove_player(server, sock);
    nets_send(&server->net, sock, "dead");
    index_client = get_player_client_index(&server->player_clients, sock);
    if (index_client == -1)
        return false;
    list_move(&server->player_clients, index_client, &server->dead_clients);
    return TRUE_SLOG(server, INFO, "Player %ld killed", player->id);
}

static bool has_to_send(net_t *net, int sock)
{
    net_transfer_t *transfer = NULL;

    for (node_t *n = net->to_send.head; n; n = n->next) {
        transfer = n->data;
        if (transfer->sock == sock) {
            return true;
        }
    }
    return false;
}

static bool sock_eq(void *a, void *b)
{
    return (*(int *)a == *(int *)b);
}

static void apply_kick(server_t *server, int *sock)
{
    if (has_to_send(&server->net, *sock))
        return;
    nets_kick(&server->net, *sock);
    list_remove_if_free(&server->dead_clients, sock_eq, sock);
    SLOG(server, DEBUG, "Kicked dead client %d", *sock);
}

bool server_kick_dead(server_t *server)
{
    if (!server)
        return false;
    list_apply(&server->dead_clients, (applicator_t)apply_kick, server);
    return true;
}
