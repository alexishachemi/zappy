/*
** EPITECH PROJECT, 2024
** socknet
** File description:
** client transfer functions
*/

#include <stdlib.h>
#include <string.h>
#include "socknet_dev.h"

static bool can_send(net_t *net, const void *data)
{
    if (!net || !data || !netc_is_connected(net))
        return FALSE_NLOG(net, ERROR, "Failed to queue transfer");
    return true;
}

bool netc_send(net_t *net, const char *data)
{
    net_transfer_t *transfer = NULL;

    if (!can_send(net, data))
        return false;
    transfer = list_add(&net->to_send, alloc_transfer);
    if (!transfer)
        return FALSE_NLOG(net, ERROR, "Failed to queue transfer");
    transfer->sock = net->sock;
    transfer->data = strdup(data);
    if (!transfer->data)
        return FALSE_NLOG(net, ERROR, "Failed to queue transfer");
    return TRUE_NLOG(net, DEBUG, "Queued transfer to server");
}

bool netc_recv(net_t *net, net_transfer_t *t_buf)
{
    net_transfer_t *transfer = NULL;

    if (!net || !t_buf)
        return FALSE_NLOG(net, ERROR, "Failed to receive transfer");
    if (!net_has_to_recv(net))
        return false;
    transfer = list_pop(&net->to_recv, 0);
    memcpy(t_buf, transfer, sizeof(net_transfer_t));
    free(transfer);
    return TRUE_NLOG(net, DEBUG, "Received transfer from server");
}
