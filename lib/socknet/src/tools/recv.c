/*
** EPITECH PROJECT, 2024
** socknet
** File description:
** packet receiving
*/

#include <string.h>
#include <stdlib.h>
#include "socknet_dev.h"

static bool handle_recv_fail(net_t *net, int sock)
{
    if (net->type == NET_SERVER) {
        NLOG(net, ERROR,
            "Failed to receive packet from socket %d, kicking client...",
                sock);
        nets_kick(net, sock);
        return true;
    } else if (net->type == NET_CLIENT) {
        NLOG(net, CRITICAL,
            "Failed to receive packet from server, disconnecting...");
        netc_disconnect(net);
    }
    return false;
}

static bool queue_transfer(net_t *net, int sock, const net_transfer_t *t)
{
    net_transfer_t *transfer = NULL;

    transfer = list_add(&net->to_recv, alloc_transfer);
    if (!transfer) {
        free(t->data);
        return FALSE_NLOG(net, ERROR,
            "Failed to queue packet received from socket %d", sock);
    }
    memcpy(transfer, t, sizeof(net_transfer_t));
    return true;
}

bool net_recv_packet(net_t *net, int sock)
{
    net_transfer_t transfer = {0};

    transfer.sock = sock;
    if (!net || sock < 0) {
        NLOG(net, ERROR, "Failed to receive packet, bad args");
        return false;
    }
    if (!net_can_read_fd(sock, SELECT_TIMEOUT_MS))
        return true;
    transfer.data = net_read_fd(sock);
    if (!transfer.data)
        return handle_recv_fail(net, sock);
    if (!queue_transfer(net, sock, &transfer))
        return true;
    return TRUE_NLOG(net, DEBUG,
        "Successfully received packet from socket %d", sock);
}

static bool server_fetch_packets(net_t *net)
{
    int *sock_ptr = NULL;
    int status = 0;

    for (size_t i = 0; i < list_size(&net->server.clients); i++) {
        sock_ptr = list_at(&net->server.clients, i);
        status = net_recv_packet(net, *sock_ptr);
        if (status == -1)
            return false;
    }
    return true;
}

static bool client_fetch_packets(net_t *net)
{
    return net_recv_packet(net, net->sock);
}

bool net_fetch_packets(net_t *net)
{
    if (!net)
        return FALSE_NLOG(net, ERROR, "Failed to fetch packets, bad args");
    if (net->type == NET_SERVER)
        return server_fetch_packets(net);
    if (net->type == NET_CLIENT)
        return client_fetch_packets(net);
    return FALSE_NLOG(net, ERROR, "Failed to fetch packets, bad type");
}
