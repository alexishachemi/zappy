/*
** EPITECH PROJECT, 2024
** socknet
** File description:
** server's clients handling
*/

#include "socknet_dev.h"

void nets_clear_sock_transfer(net_t *net, int sock)
{
    net_transfer_t *transfer = NULL;

    if (!net)
        return NLOG(net, ERROR, "Couldn't clear client %s's packets", sock);
    for (size_t i = 0; i < list_size(&net->to_send); i++) {
        transfer = list_at(&net->to_send, i);
        if (transfer->sock == sock) {
            list_remove(&net->to_send, free_transfer, i);
            i--;
        }
    }
    NLOG(net, DEBUG, "Cleared all to_send packets of client %d", sock);
}

bool nets_fetch_clients(net_t *net)
{
    int *sock_ptr = NULL;
    int sock = -1;

    if (!net)
        return FALSE_NLOG(net, ERROR, "Couldn't fetch clients");
    if (!net_can_read_fd(net->sock, SELECT_TIMEOUT_MS))
        return true;
    sock = accept(net->sock, NULL, NULL);
    if (sock < 0)
        return FALSE_NLOG(net, ERROR, "Failed to accept client");
    sock_ptr = list_add(&net->server.incoming, alloc_sock);
    if (!sock_ptr) {
        close(sock);
        return FALSE_NLOG(net, ERROR, "Failed to add client to list");
    }
    *sock_ptr = sock;
    return TRUE_NLOG(net, DEBUG, "Successfully fetched client %d", sock);
}
