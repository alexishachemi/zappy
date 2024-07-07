/*
** EPITECH PROJECT, 2024
** socknet
** File description:
** initialization functions
*/

#include <string.h>
#include "socknet_dev.h"

bool net_init(net_t *net, port_t port, const char *log_path, bool use_stdout)
{
    if (!net)
        return false;
    memset(net, 0, sizeof(net_t));
    if (!logger_init(&net->logger, log_path, true, use_stdout ? stdout : NULL))
        return false;
    net->type = NET_NO_TYPE;
    net->sock = net_open_socket(port);
    net->port = net_get_port(net->sock);
    if (net->sock == -1) {
        NLOG(net, CRITICAL, "Failed to open socket");
        logger_deinit(&net->logger);
        return false;
    }
    return TRUE_NLOG(net, INFO, "Initialized network module on port %d",
        net->port);
}

static void deinit_server(net_t *net)
{
    list_clear(&net->server.clients, free_sock);
    list_clear(&net->server.incoming, free_sock);
    list_clear(&net->server.outgoing, free_sock);
    close(net->sock);
    NLOG(net, INFO, "Deinitialized server");
}

static void deinit_client(net_t *net)
{
    if (netc_is_connected(net))
        netc_disconnect(net);
    NLOG(net, INFO, "Deinitialized client");
}

void net_deinit(net_t *net)
{
    if (!net)
        return;
    logger_deinit(&net->logger);
    if (net->type == NET_SERVER)
        deinit_server(net);
    else if (net->type == NET_CLIENT)
        deinit_client(net);
    list_clear(&net->to_recv, free_transfer);
    list_clear(&net->to_send, free_transfer);
}
