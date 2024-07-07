/*
** EPITECH PROJECT, 2024
** socknet
** File description:
** net_tests_utils
*/

#include <stdlib.h>
#include <string.h>
#include "socknet.h"

net_transfer_t *create_transfer(int sock, const char *data)
{
    net_transfer_t *transfer = malloc(sizeof(net_transfer_t));

    if (!transfer)
        return NULL;
    transfer->sock = sock;
    transfer->data = strdup(data);
    if (!transfer->data) {
        free(transfer);
        return NULL;
    }
    return transfer;
}
