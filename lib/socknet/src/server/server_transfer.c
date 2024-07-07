/*
** EPITECH PROJECT, 2024
** zappy [WSL: Ubuntu]
** File description:
** server_transfer
*/

#include <stdlib.h>
#include <string.h>
#include "socknet_dev.h"

static bool can_send(net_t *net, int sock, const void *data)
{
    if (!net || sock < 0 || !data || !nets_sock_is_client(net, sock))
        return FALSE_NLOG(net, ERROR, "Failed to queue transfer data");
    return true;
}

bool nets_send(net_t *net, int sock, const char *data)
{
    net_transfer_t *transfer = NULL;
    size_t size = 0;

    if (!can_send(net, sock, data))
        return false;
    transfer = list_add(&net->to_send, alloc_transfer);
    if (!transfer)
        return FALSE_NLOG(net, ERROR, "Failed to queue transfer");
    size = strlen(data) + 2;
    transfer->sock = sock;
    transfer->data = malloc(size);
    memset(transfer->data, 0, size);
    if (!transfer->data) {
        free_transfer(transfer);
        return FALSE_NLOG(net, ERROR, "Failed to queue transfer");
    }
    strcat(transfer->data, data);
    strcat(transfer->data, "\n");
    return TRUE_NLOG(net, DEBUG, "Queued transfer to client %d", sock);
}

static void remove_trailing_newline(char *str)
{
    size_t size = 0;

    size = strlen(str);
    if (size > 0 && str[size - 1] == '\n')
        str[size - 1] = 0;
}

bool nets_recv(net_t *net, net_transfer_t *t_buf)
{
    net_transfer_t *transfer = NULL;

    if (!net || !t_buf)
        return FALSE_NLOG(net, ERROR, "Failed to dequeue received transfer");
    if (!net_has_to_recv(net))
        return false;
    transfer = list_pop(&net->to_recv, 0);
    remove_trailing_newline(transfer->data);
    memcpy(t_buf, transfer, sizeof(net_transfer_t));
    free(transfer);
    return TRUE_NLOG(net, DEBUG, "Dequeued transfer received from client %d",
        t_buf->sock);
}
