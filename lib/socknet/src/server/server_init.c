/*
** EPITECH PROJECT, 2024
** socknet
** File description:
** server initialization
*/

#include "socknet_dev.h"

static void init_lists(net_t *net)
{
    list_init(&net->server.clients);
    list_init(&net->server.incoming);
    list_init(&net->server.outgoing);
}

bool nets_host(net_t *net)
{
    if (!net)
        return false;
    if (listen(net->sock, QUEUE_SIZE) == -1) {
        NLOG(net, CRITICAL, "Failed to listen on socket");
        logger_deinit(&net->logger);
        close(net->sock);
        return false;
    }
    net->type = NET_SERVER;
    init_lists(net);
    return TRUE_NLOG(net, INFO, "Server hosted");
}
