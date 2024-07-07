/*
** EPITECH PROJECT, 2024
** socknet
** File description:
** list state functions
*/

#include "socknet_dev.h"

bool net_has_to_send(const net_t *net)
{
    return net && !list_empty(&net->to_send);
}

bool net_has_to_recv(const net_t *net)
{
    return net && !list_empty(&net->to_recv);
}

bool nets_has_incoming(const net_t *net)
{
    return net && !list_empty(&net->server.incoming);
}

bool nets_has_outgoing(const net_t *net)
{
    return net && !list_empty(&net->server.outgoing);
}
