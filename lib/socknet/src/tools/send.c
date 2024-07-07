/*
** EPITECH PROJECT, 2024
** socknet
** File description:
** packet sending
*/

#include <string.h>
#include "socknet_dev.h"

static bool handle_send_fail(net_t *net, int sock, int size, int status)
{
    if (net->type == NET_SERVER) {
        NLOG(net, CRITICAL,
            "Failed to send packet to socket %d (size: %d, status: %d), "
            "kicking client...", sock, size, status);
        nets_kick(net, sock);
        return true;
    } else if (net->type == NET_CLIENT) {
        NLOG(net, CRITICAL,
            "Failed to send packet to server (size: %d, status: %d), "
            "disconnecting...", size, status);
        netc_disconnect(net);
    }
    return false;
}

bool net_send_packet(net_t *net, const net_transfer_t *transfer)
{
    int status = 0;
    int sock = -1;
    size_t size = strlen(transfer->data);

    if (!net || !transfer || transfer->sock < 0)
        return FALSE_NLOG(net, ERROR, "Failed to send packet, bad args");
    if (!net_can_write_fd(transfer->sock, SELECT_TIMEOUT_MS))
        return FALSE_NLOG(net, DEBUG, "Cannot write to socket %d",
            transfer->sock);
    sock = transfer->sock;
    status = write(sock, transfer->data, size);
    if ((unsigned int)status != size)
        return handle_send_fail(net, sock, size, status);
    return TRUE_NLOG(net, DEBUG, "Successfully sent packet to socket %d",
        sock);
}

bool net_send_queued(net_t *net)
{
    net_transfer_t *transfer = NULL;

    if (!net)
        return FALSE_NLOG(net, ERROR,
            "Failed to send queued packets, bad args");
    while (net_has_to_send(net)) {
        transfer = list_at(&net->to_send, 0);
        if (!net_send_packet(net, transfer))
            return false;
        list_remove(&net->to_send, free_transfer, 0);
    }
    return true;
}
