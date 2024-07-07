/*
** EPITECH PROJECT, 2024
** socknet
** File description:
** server client handling
*/

#include <stdlib.h>
#include <string.h>
#include "socknet_dev.h"

bool nets_accept_incoming(net_t *net, int *sock_buf)
{
    int *sock_ptr = NULL;

    if (!net || !sock_buf)
        return FALSE_NLOG(net, ERROR,
            "Failed to accept incoming connection, bad args");
    if (!nets_has_incoming(net))
        return false;
    if (!list_move(&net->server.incoming, 0, &net->server.clients))
        return FALSE_NLOG(net, ERROR, "Failed to accept incoming connection");
    sock_ptr = list_at(&net->server.clients, -1);
    memcpy(sock_buf, sock_ptr, sizeof(int));
    return TRUE_NLOG(net, INFO, "Accepted incoming client %d",
        *sock_buf);
}

bool nets_accept_outgoing(net_t *net, int *sock_buf)
{
    int *sock_ptr = NULL;

    if (!net || !sock_buf)
        return FALSE_NLOG(net, ERROR,
            "Failed to accept outgoing connection");
    if (!nets_has_outgoing(net))
        return false;
    sock_ptr = list_pop(&net->server.outgoing, 0);
    memcpy(sock_buf, sock_ptr, sizeof(int));
    free(sock_ptr);
    close(*sock_buf);
    return TRUE_NLOG(net, INFO, "Accepted outgoing client %d",
        *sock_buf);
}

bool nets_kick(net_t *net, int sock)
{
    bool found = false;
    int *sock_ptr = NULL;
    size_t i = 0;

    if (!net || sock < 0)
        return FALSE_NLOG(net, ERROR, "Failed to kick client %d", sock);
    for (node_t *n = net->server.clients.head; n; n = n->next) {
        sock_ptr = n->data;
        if (*sock_ptr == sock) {
            found = true;
            break;
        }
        i++;
    }
    if (!found
        || !list_move(&net->server.clients, i, &net->server.outgoing))
        return FALSE_NLOG(net, ERROR, "Failed to kick client %d", sock);
    nets_clear_sock_transfer(net, *sock_ptr);
    return TRUE_NLOG(net, INFO, "Kicked client %d", sock);
}

bool nets_sock_is_client(net_t *net, int sock)
{
    if (!net)
        return false;
    for (node_t *n = net->server.clients.head; n; n = n->next) {
        if (*(int *)n->data == sock) {
            return true;
        }
    }
    return false;
}
