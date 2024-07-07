/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** test_client
*/

#include <stdlib.h>
#include <string.h>
#include "socknet.h"

static bool handle_packets(net_t *net)
{
    net_transfer_t transfer = {0};
    char *str = NULL;

    if (net_can_read_fd(0, 100)) {
        str = net_read_fd(0);
        if (!str)
            return false;
        netc_send(net, str);
        free(str);
    }
    while (netc_recv(net, &transfer)) {
        printf("%s", transfer.data);
        free(transfer.data);
    }
    return true;
}

static int get_port(int ac, char **av, int i)
{
    if (ac < i + 1)
        return -1;
    return atoi(av[i]);
}

int main(int ac, char **av)
{
    net_t net;
    int port = get_port(ac, av, ac == 2 ? 1 : 2);

    if (port <= 0 || !(net_init(&net, 0, "client.log", false)
        && net_set_log_level(&net, DEBUG)
        && netc_connect(&net, ac == 2 ? "127.0.0.1" : av[1], (port_t)port)))
        return 84;
    while (net_update(&net) == NET_OK) {
        if (!handle_packets(&net))
            break;
    }
    net_deinit(&net);
    return 0;
}
