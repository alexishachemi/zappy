/*
** EPITECH PROJECT, 2024
** socknet
** File description:
** allocators
*/

#include <stdlib.h>
#include "socknet_dev.h"

void *alloc_sock(void)
{
    return malloc(sizeof(int));
}

void *alloc_transfer(void)
{
    return malloc(sizeof(net_transfer_t));
}

void free_transfer(void *t)
{
    net_transfer_t *transfer = t;

    if (!transfer)
        return;
    if (transfer->data)
        free(transfer->data);
    free(transfer);
}

void free_sock(void *c)
{
    int *sock = c;

    if (!sock)
        return;
    if (*sock >= 0)
        close(*sock);
    free(sock);
}
